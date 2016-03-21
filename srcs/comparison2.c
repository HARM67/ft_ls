/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 20:55:33 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/21 21:00:42 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	compare_size2(t_app *app, char *elm1, char *elm2)
{
	t_stat	st1;
	t_stat	st2;

	app = 0;
	lstat(elm1, &st1);
	lstat(elm2, &st2);
	if (st1.st_size >= st2.st_size)
		return (1);
	return (0);
}

int	compare_ascii2(t_app *app, char *elm1, char *elm2)
{
	app = 0;
	if (ft_strcmp(elm1, elm2) <= 0)
		return (1);
	return (0);
}

int	compare_modif2(t_app *app, char *elm1, char *elm2)
{
	t_stat	st1;
	t_stat	st2;

	app = 0;
	lstat(elm1, &st1);
	lstat(elm2, &st2);
	if (st1.st_mtimespec.tv_sec > st2.st_mtimespec.tv_sec)
		return (1);
	else if (st1.st_mtimespec.tv_sec == st2.st_mtimespec.tv_sec &&
		st1.st_mtimespec.tv_nsec >= st2.st_mtimespec.tv_nsec)
		return (1);
	return (0);
}
