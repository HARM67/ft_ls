/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 21:16:01 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/21 21:23:52 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_p_arg	*new_p_arg(t_app *app, char *path)
{
	t_p_arg *rt;

	app = 0;
	rt = (t_p_arg*)ft_memalloc(sizeof(t_p_arg));
	if (!rt)
		exit(1);
	rt->path = path;
	return (rt);
}

void	insert_p_arg_2(t_app *app, t_p_arg *new, t_p_arg *tmp)
{
	while (tmp->next)
	{
		if (app->compare2(app, tmp->path, new->path) &&
			app->compare2(app, new->path, tmp->next->path))
		{
			tmp->next->previous = new;
			new->next = tmp->next;
			tmp->next = new;
			new->previous = tmp;
			return ;
		}
		tmp = tmp->next;
	}
	tmp->next = new;
	new->previous = tmp;
	app->last_p_arg = new;
}

void	insert_p_arg(t_app *app, char *path)
{
	t_p_arg	*new;
	t_p_arg	*tmp;

	if (*path == 0)
		put_error("ft_ls: fts_open: No such file or directory");
	tmp = app->first_p_arg;
	new = new_p_arg(app, path);
	if (!app->nb_p_arg)
	{
		app->first_p_arg = new;
		app->last_p_arg = new;
		app->nb_p_arg++;
		return ;
	}
	app->nb_p_arg++;
	if (app->compare2(app, new->path, tmp->path))
	{
		tmp->previous = new;
		new->next = tmp;
		app->first_p_arg = new;
		return ;
	}
	insert_p_arg_2(app, new, tmp);
}

void	read_arg(t_app *app)
{
	int	i;

	i = 1;
	while (i < app->ac)
	{
		if (!app->read_mode && app->av[i][0] == '-' &&
				check_arg(app, app->av[i]))
			;
		else
		{
			insert_p_arg(app, app->av[i]);
			app->read_mode = 1;
		}
		i++;
	}
	if (app->nb_p_arg > 1)
		app->recursive_depth++;
	if (app->nb_p_arg == 0)
		insert_p_arg(app, ".");
}
