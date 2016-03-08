/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 13:31:19 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/08 14:25:42 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	compare_size(t_app *app, t_elem *elm1, t_elem *elm2)
{
	if (elm1->stat.st_size <= elm2->stat.st_size && !app->reverse_sort)
		return (1);
	if (elm1->stat.st_size >= elm2->stat.st_size && app->reverse_sort)
		return (1);
	return (0);
}

int	compare_ascii(t_app *app, t_elem *elm1, t_elem *elm2)
{
	if (ft_strcmp(elm1->name, elm2->name) <= 0 && !app->reverse_sort)
		return (1);
	if (ft_strcmp(elm1->name, elm2->name) >= 0 && app->reverse_sort)
		return (1);
	return (0);
}
