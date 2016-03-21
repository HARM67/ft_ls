/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 13:31:19 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/21 15:12:57 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	compare_size(t_app *app, t_elem *elm1, t_elem *elm2)
{
	app = 0;
	if (elm1->stat.st_size >= elm2->stat.st_size)
		return (1);
	return (0);
}

int	compare_ascii(t_app *app, t_elem *elm1, t_elem *elm2)
{
	app = 0;
	if (ft_strcmp(elm1->name, elm2->name) <= 0)
		return (1);
	return (0);
}

int	compare_modif(t_app *app, t_elem *elm1, t_elem *elm2)
{
	app = 0;
	if (elm1->stat.st_mtimespec.tv_sec > elm2->stat.st_mtimespec.tv_sec)
		return (1);
	else if (elm1->stat.st_mtimespec.tv_sec == elm2->stat.st_mtimespec.tv_sec &&
		elm1->stat.st_mtimespec.tv_nsec >= elm2->stat.st_mtimespec.tv_nsec)
		return (1);
	return (0);
}
