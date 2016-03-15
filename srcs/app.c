/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 02:59:03 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/14 06:14:57 by mfroehly         ###   ########.fr       */
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
	app->print(app, &lst);
	if (app->have_file && app->have_dir)
		ft_putchar('\n');
	clean_lst(&lst);
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
				ft_printf("ft_ls: %s: No such file or directory\n", tmp->path);
		}
		else
			app->have_dir = 1;
		tmp = tmp->next;
	}
}

void	run_app(t_app *app)
{
	t_p_arg	*tmp;

	read_arg(app);
	tmp = app->first_p_arg;
	check_invalide(app);
	print_file(app);
	while (tmp)
	{
		push_path(app, tmp->path);
		parcour(app);
		pop_path(app);
		tmp = tmp->next;
	}
}
