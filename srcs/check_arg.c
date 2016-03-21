/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 15:05:57 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/21 21:33:51 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	check_arg_3(t_app *app, char *arg, int i)
{
	if (arg[i] == 'S')
	{
		app->compare = *compare_size;
		app->compare2 = *compare_size2;
	}
	else if (arg[i] == 't')
	{
		app->compare = *compare_modif;
		app->compare2 = *compare_modif2;
	}
	else
	{
		ft_fprintf(2, "ft_ls: illegal option -- %c\n"
		"usage: ls [-GRSalrt] [file ...]", arg[i]);
		exit(1);
	}
	return (0);
}

static int	check_arg_2(t_app *app, char *arg, int i)
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
	else
		check_arg_3(app, arg, i);
	return (0);
}

int			check_arg(t_app *app, char *arg)
{
	unsigned int	rt;
	unsigned int	size;
	unsigned int	i;

	i = 0;
	rt = 0;
	if (ft_strcmp(arg, "--") == 0)
	{
		app->read_mode = 1;
		return (1);
	}
	size = ft_strlen(arg);
	while (++i < size)
	{
		if (check_arg_2(app, arg, i))
			return (0);
		rt = 1;
	}
	return (rt);
}
