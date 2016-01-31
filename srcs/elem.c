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

void	print_elem(t_elem *elm, t_lst_elem *lst)
{
	write_mode(elm->stat.st_mode);
	ft_printf(" %*d %s %s\n", lst->max_size, elm->stat.st_size, elm->user_name,elm->name);
}

void	push_elem(t_app *app, t_lst_elem *lst, struct dirent *d)
{
	struct passwd	*pswd;

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
	//lst->last->groupe_name = pswd->
	//free(pswd);

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
