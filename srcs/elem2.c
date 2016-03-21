/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:36:17 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/21 14:37:58 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	pop_elem(t_lst_elem *lst)
{
	t_elem	*tmp;

	tmp = lst->last;
	if (!lst->nb_elem)
		return ;
	else if (lst->nb_elem != 1)
	{
		lst->last = lst->last->previous;
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
