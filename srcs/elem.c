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

static void	write_attribut(char *path)
{
	//ft_printf("%d",getxattr(path, "", 0, 0, 0, 0));
	//	ft_printf("@");
	//else
		ft_printf(" ");
}

void	print_date(char *date)
{
	unsigned int i;

	i = 4;
	while (i <= 15)
	{
		ft_putchar(date[i]);
		i++;
	}
}

void	print_elem(t_elem *elm, t_lst_elem *lst)
{
	write_mode(elm->stat.st_mode);
	write_attribut("/");
	ft_printf(" %*d %-*s  %-*s  %*d %d ",
			nbr_len(lst->max_nlink),  elm->stat.st_nlink,
			lst->max_name_len, elm->user_name,
			lst->max_grp_len, elm->groupe_name,
			lst->max_size, elm->stat.st_size,
			elm->stat.st_mtimespec.tv_sec/*,
			elm->name*/);
	print_date(ctime(&elm->stat.st_mtimespec.tv_sec));
	ft_printf(" %s\n",elm->name );

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

	pswd = getpwuid(rt->stat.st_uid);
	rt->user_name = pswd->pw_name;
	rt->name_len = ft_strlen(rt->user_name);
	if (rt->name_len > lst->max_name_len)
		lst->max_name_len = rt->name_len;

	grp = getgrgid(rt->stat.st_gid);
	rt->groupe_name = grp->gr_name;
	rt->grp_len = ft_strlen(rt->groupe_name);
	if (rt->grp_len > lst->max_grp_len)
		lst->max_grp_len = rt->grp_len;

	if (rt->stat.st_size > lst->max_size)
		lst->max_size = rt->stat.st_size;
	if (rt->stat.st_nlink > lst->max_nlink)
		lst->max_nlink = rt->stat.st_nlink;
	return (rt);
}

void	insert_elm(t_app *app, t_lst_elem *lst, struct dirent *d)
{
	t_elem	*elm;
	t_elem	*n_elm;

	if (d->d_name[0] == '.' && !app->show_hidden)
		return ;
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

void	push_elem(t_app *app, t_lst_elem *lst, struct dirent *d)
{
	struct passwd	*pswd;
	struct group	*grp;

	if (!lst->nb_elem)
	{
		lst->first = new_elem(d);
		lst->last = lst->first;
	}
	else
	{
		lst->last->next = new_elem(d);
		lst->last->next->previous = lst->last;
		lst->last = lst->last->next;
	}
	push_path(app, lst->last->name);
	lst->last->path = path_str(app, 0);
	pop_path(app);
	read_stat(lst->last);
	lst->last->dirent = d;

	pswd = getpwuid(lst->last->stat.st_uid);
	lst->last->user_name = pswd->pw_name;
	lst->last->name_len = ft_strlen(lst->last->user_name);
	if (lst->last->name_len > lst->max_name_len)
		lst->max_name_len = lst->last->name_len;

	grp = getgrgid(lst->last->stat.st_gid);
	lst->last->groupe_name = grp->gr_name;
	lst->last->grp_len = ft_strlen(lst->last->groupe_name);
	if (lst->last->grp_len > lst->max_grp_len)
		lst->max_grp_len = lst->last->grp_len;

	if (lst->last->stat.st_size > lst->max_size)
		lst->max_size = lst->last->stat.st_size;
	lst->nb_elem++;
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
		if (tmp->path)
			free(tmp->path);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp->next;
		tmp = tmp2;
	}
}
