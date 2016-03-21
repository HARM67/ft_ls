/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 03:24:45 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/21 14:39:28 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		prepare_elem_2(t_lst_elem *lst, t_elem *rt)
{
	if (rt->name_len > lst->max_file_name)
		lst->max_file_name = rt->name_len;
	if (rt->user_len > lst->max_name_len)
		lst->max_name_len = rt->user_len;
	if (rt->grp_len > lst->max_grp_len)
		lst->max_grp_len = rt->grp_len;
	if (rt->stat.st_size > lst->max_size)
		lst->max_size = rt->stat.st_size;
	if (rt->stat.st_nlink > lst->max_nlink)
		lst->max_nlink = rt->stat.st_nlink;
	lst->total += rt->stat.st_blocks;
	if ((rt->stat.st_mode & 0770000) == 0060000 ||
			(rt->stat.st_mode & 0770000) == 0020000)
		lst->have_periph = 1;
	if ((rt->stat.st_mode & 0770000) == 0120000)
		readlink(rt->path, rt->link_path, 256);
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
	rt->user_len = ft_strlen(rt->user_name);
	grp = getgrgid(rt->stat.st_gid);
	rt->groupe_name = grp->gr_name;
	rt->grp_len = ft_strlen(rt->groupe_name);
	prepare_elem_2(lst, rt);
	return (rt);
}

int				insert_elm_front(t_lst_elem *lst, t_elem *n_elm)
{
	if (!lst->nb_elem)
	{
		lst->first = n_elm;
		lst->last = n_elm;
		lst->nb_elem++;
		return (1);
	}
	return (0);
}

void			insert_elm_2(t_app *app, t_lst_elem *lst, t_elem *n_elm,
								t_elem *elm)
{
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

void			insert_elm(t_app *app, t_lst_elem *lst, struct dirent *d)
{
	t_elem	*elm;
	t_elem	*n_elm;

	if (d->d_name[0] == '.' && !app->show_hidden)
		return ;
	lst->size++;
	elm = lst->first;
	n_elm = prepare_elem(app, lst, d);
	if (insert_elm_front(lst, n_elm))
		return ;
	lst->nb_elem++;
	if (app->compare(app, n_elm, elm))
	{
		elm->previous = n_elm;
		n_elm->next = elm;
		lst->first = n_elm;
		return ;
	}
	insert_elm_2(app, lst, n_elm, elm);
}
