/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:13:25 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/21 21:33:59 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parcour2(t_app *app, t_lst_elem *lst)
{
	t_elem			*tmp;

	tmp = (app->reverse_sort) ? lst->last : lst->first;
	if (app->recursive)
		while (tmp)
		{
			push_path(app, tmp->name);
			if ((tmp->stat.st_mode & 0040000) && tmp->name[0] != '.')
				parcour(app);
			pop_path(app);
			tmp = (app->reverse_sort) ? tmp->previous : tmp->next;
		}
	clean_lst(lst);
	app->recursive_depth--;
}

void	parcour(t_app *app)
{
	DIR				*dirp;
	struct dirent	*d;
	char			*path;
	t_lst_elem		lst;

	path = path_str(app, 1);
	dirp = opendir(path);
	if (dirp == 0)
	{
		free(path);
		return ;
	}
	ft_bzero(&lst, sizeof(t_lst_elem));
	if (app->temoin++)
		ft_putchar('\n');
	if (app->recursive_depth)
		ft_printf("%s:\n", path);
	app->recursive_depth++;
	free(path);
	while ((d = readdir(dirp)))
		insert_elm(app, &lst, d);
	app->print(app, &lst);
	parcour2(app, &lst);
	closedir(dirp);
	free(d);
}
