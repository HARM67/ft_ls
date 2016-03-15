#include "ft_ls.h"

t_elem	*new_elem(struct dirent *d)
{
	t_elem *rt;

	rt = (t_elem*)ft_memalloc(sizeof(t_elem));
	if (rt == 0)
		exit(1);
	ft_strcpy(rt->name, d->d_name);
	rt->name_len = d->d_namlen;
	rt->type = d->d_type;
	return (rt);
}

static void	write_attribut(t_elem *elm)
{
	char	*path;

	if ((elm->stat.st_mode & 0120000) == 0120000)
		path = elm->link_path;
	else
		path = elm->path;
	if (listxattr(path, 0, 0, 0) > 0)
		ft_printf("@");
	else
		ft_printf(" ");
}

void	print_date(t_app *app, time_t elm_time)
{
	unsigned int i;
	char		*date;

	date = ctime(&elm_time);
	i = 3;
	if ((time(0) - elm_time) < 15552000)
		while (++i <= 15)
			ft_putchar(date[i]);
	else
	{
		while (++i <= 10)
			ft_putchar(date[i]);
		i = 18;
		while (++i <= 23)
			ft_putchar(date[i]);
	}
}


void	print_elem_list(t_app *app, t_elem *elm, t_lst_elem *lst)
{
	char buf[256];

	ft_bzero(buf, 256);
	write_mode(elm->stat.st_mode);
	write_attribut(elm);
	ft_printf(" %*d %-*s  %-*s  %*d ",
		nbr_len(lst->max_nlink),  elm->stat.st_nlink,
		lst->max_name_len, elm->user_name,
		lst->max_grp_len, elm->groupe_name, lst->max_size, elm->stat.st_size);
	print_date(app, elm->stat.st_mtimespec.tv_sec);
	ft_putchar(' ');
	lst->max_file_name = 0;
	print_name(app, lst, elm);
	if ((elm->stat.st_mode & 0120000) == 0120000)
	{
		readlink(elm->path, buf, 256);
		ft_printf(" -> %s", buf);
	}
	ft_putchar('\n');
}

static t_elem	*prepare_elem(t_app *app, t_lst_elem *lst, struct dirent *d)
{
	t_elem			*rt;
	struct passwd	*pswd;
	struct group	*grp;

	rt = new_elem(d);

	push_path(app, rt->name);
	rt->path = path_str(app, 0);
	pop_path(app);
	read_stat(rt);
	rt->dirent = d;
	if (rt->name_len > lst->max_file_name)
		lst->max_file_name = rt->name_len;

	pswd = getpwuid(rt->stat.st_uid);
	rt->user_name = pswd->pw_name;
	rt->user_len = ft_strlen(rt->user_name);
	if (rt->user_len > lst->max_name_len)
		lst->max_name_len = rt->user_len;

	grp = getgrgid(rt->stat.st_gid);
	rt->groupe_name = grp->gr_name;
	rt->grp_len = ft_strlen(rt->groupe_name);
	if (rt->grp_len > lst->max_grp_len)
		lst->max_grp_len = rt->grp_len;

	if (rt->stat.st_size > lst->max_size)
		lst->max_size = rt->stat.st_size;
	if (rt->stat.st_nlink > lst->max_nlink)
		lst->max_nlink = rt->stat.st_nlink;
	lst->total += rt->stat.st_blocks;

	if ((rt->stat.st_mode & 0120000) == 0120000)
		readlink(rt->path, rt->link_path, 256);
	return (rt);
}

void	insert_elm(t_app *app, t_lst_elem *lst, struct dirent *d)
{
	t_elem	*elm;
	t_elem	*n_elm;

	if (d->d_name[0] == '.' && !app->show_hidden)
		return ;
	lst->size++;
	elm = lst->first;
	n_elm = prepare_elem(app, lst, d);
	if (!lst->nb_elem)
	{
		lst->first = n_elm;
		lst->last = n_elm;
		lst->nb_elem++;
		return ;
	}
	lst->nb_elem++;
	if (app->compare(app, n_elm, elm))
	{
		elm->previous = n_elm;
		n_elm->next = elm;
		lst->first = n_elm;
		return ;
	}
	while (elm->next)
	{
		if (app->compare(app, elm, n_elm) &&
			app->compare(app, n_elm, elm->next))
		{
			elm->next->previous = n_elm;
			n_elm->next = elm->next;
			elm->next = n_elm;
			n_elm->previous = elm;
			return ;
		}
		elm = elm->next;
	}
	elm->next = n_elm;
	n_elm->previous = elm;
	lst->last = n_elm;
}

void	pop_elem(t_lst_elem *lst)
{
	t_elem	*tmp;

	tmp = lst->last;
	if (!lst->nb_elem)
		return ;
	else if (lst->nb_elem != 1)
	{
		lst->last= lst->last->previous;
		lst->last->next = 0;
	}
	free(tmp);
	lst->nb_elem--;
}

void	clean_lst(t_lst_elem *lst)
{
	t_elem *tmp;
	t_elem *tmp2;

	tmp = lst->first;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->path)
			free(tmp->path);
		free(tmp);
		tmp = tmp2;
	}
}
