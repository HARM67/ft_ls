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

void	push_elem(t_lst_elem *lst, struct dirent *d)
{
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

