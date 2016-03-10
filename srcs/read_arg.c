/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 21:16:01 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/10 15:56:34 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_p_arg	*new_p_arg(t_app *app, char *path)
{
	t_p_arg *rt;

	rt = (t_p_arg*)ft_memalloc(sizeof(t_p_arg));
	if (!rt)
		exit (1);
	rt->path = path;
	return (rt);
}

void	insert_p_arg(t_app *app, char *path)
{
	t_p_arg	*new;
	t_p_arg	*tmp;

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
	if (ft_strcmp(new->path, tmp->path) <= 0)
	{
		tmp->previous = new;
		new->next = tmp;
		app->first_p_arg = new;
		return ;
	}
	while (tmp->next)
	{
		if (ft_strcmp(tmp->path, new->path) <= 0 &&
			ft_strcmp(new->path, tmp->next->path) <= 0)
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

int		check_arg(t_app *app, char *arg)
{
	unsigned int	rt;
	unsigned int	size;
	unsigned int	i;

	i = 1;
	rt = 0;
	if (ft_strcmp(arg, "--") == 0 )
	{
		app->read_mode = 1;
		return (1);
	}
	size = ft_strlen(arg);
	while (i < size)
	{
		if (arg[i] == 'l')
			app->print = *print_lst_list;
		else if (arg[i] == 'R')
			app->recursive = 1;
		else if (arg[i] == 'G')
			app->color = 1;
		else if (arg[i] == 'a')
			app->show_hidden = 1;
		else if (arg[i] == 'r')
			app->reverse_sort = 1;
		rt = 1;
		i++;
	}
	return (rt);
}

void		read_arg(t_app *app)
{
	unsigned int	i;

	i = 1;
	while (i < app->ac)
	{
		if (!app->read_mode && app->av[i][0] == '-' &&
				check_arg(app, app->av[i]))
			;
		else
			insert_p_arg(app, app->av[i]);
		i++;
	}
	if (app->nb_p_arg > 1)
		app->recursive_depth++;
	if (app->nb_p_arg == 0)
		insert_p_arg(app, ".");
}
