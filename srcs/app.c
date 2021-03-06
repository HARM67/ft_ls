/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 02:59:03 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/21 21:23:32 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_app(t_app *app)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	app->row = w.ws_row;
	app->col = w.ws_col;
	app->compare = *compare_ascii;
	app->compare2 = *compare_ascii2;
	app->print = *print_lst;
}

void	print_file(t_app *app)
{
	t_p_arg			*tmp;
	t_lst_elem		lst;
	struct dirent	d;

	tmp = app->first_p_arg;
	ft_bzero(&lst, sizeof(t_lst_elem));
	lst.no_total = 1;
	while (tmp)
	{
		if (tmp->type == 1)
		{
			ft_strcpy(d.d_name, tmp->path);
			d.d_namlen = ft_strlen(d.d_name);
			insert_elm(app, &lst, &d);
		}
		tmp = tmp->next;
	}
	if (app->have_file)
		app->print(app, &lst);
	if (app->have_file && app->have_dir)
		ft_putchar('\n');
}

void	print_errno(t_p_arg *tmp)
{
	if (errno == 13)
		ft_printf("ft_ls: %s: Permission denied\n", tmp->path);
	else
		ft_printf("ft_ls: %s: No such file or directory\n", tmp->path);
}

void	check_invalide(t_app *app)
{
	DIR		*dirp;
	t_p_arg	*tmp;

	tmp = app->first_p_arg;
	while (tmp)
	{
		dirp = opendir(tmp->path);
		if (dirp == 0)
		{
			if (errno == 20)
			{
				tmp->type = 1;
				app->have_file = 1;
			}
			else
				print_errno(tmp);
		}
		else
		{
			app->have_dir = 1;
			closedir(dirp);
		}
		tmp = tmp->next;
	}
}

void	run_app(t_app *app)
{
	t_p_arg	*tmp;
	t_p_arg	*tmp2;

	read_arg(app);
	check_invalide(app);
	print_file(app);
	tmp = (app->reverse_sort) ? app->last_p_arg : app->first_p_arg;
	while (tmp)
	{
		tmp2 = (app->reverse_sort) ? tmp->previous : tmp->next;
		push_path(app, tmp->path);
		parcour(app);
		pop_path(app);
		free(tmp);
		tmp = tmp2;
	}
}
