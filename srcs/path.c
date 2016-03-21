/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:10:05 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/21 15:11:06 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path	*new_path(char *str)
{
	t_path	*rt;

	rt = (t_path*)ft_memalloc(sizeof(t_path));
	if (rt == 0)
		exit(1);
	rt->str = ft_strdup(str);
	rt->len = ft_strlen(str);
	return (rt);
}

void	push_path(t_app *app, char *str)
{
	if (!app->nb_path)
	{
		app->first_path = new_path(str);
		app->last_path = app->first_path;
		app->path_len += app->first_path->len;
	}
	else
	{
		app->last_path->next = new_path(str);
		app->last_path->next->previous = app->last_path;
		app->last_path = app->last_path->next;
		app->path_len += app->last_path->len;
	}
	app->nb_path++;
}

void	pop_path(t_app *app)
{
	t_path	*tmp;

	tmp = app->last_path;
	if (!app->nb_path)
		return ;
	else if (app->nb_path != 1)
	{
		app->last_path = app->last_path->previous;
		app->last_path->next = 0;
	}
	app->path_len -= tmp->len;
	free(tmp->str);
	free(tmp);
	app->nb_path--;
}

void	print_path(t_app *app)
{
	t_path			*tmp;
	unsigned int	i;

	tmp = app->first_path;
	i = app->nb_path;
	while (i && tmp)
	{
		ft_putstr(tmp->str);
		ft_putstr("/");
		tmp = tmp->next;
		i--;
	}
	ft_putstr("\n");
}

char	*path_str(t_app *app, char option)
{
	char			*rt;
	t_path			*tmp;
	unsigned int	i;

	option = 0;
	tmp = app->first_path;
	i = app->nb_path;
	rt = (char*)ft_memalloc(sizeof(char) * (app->path_len + i + 1));
	if (rt == 0)
		exit(1);
	while (i && tmp)
	{
		ft_strcat(rt, tmp->str);
		if (tmp->next && ft_strcmp(tmp->str, "/"))
			ft_strcat(rt, "/");
		tmp = tmp->next;
		i--;
	}
	ft_strcat(rt, "\0");
	return (rt);
}
