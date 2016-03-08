/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 14:31:54 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/08 20:10:22 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned int	nbr_len(unsigned int nbr)
{
	unsigned int	rt;
	char			*tmp;

	tmp = uitoa_base_4(nbr, 10);
	rt = ft_strlen(tmp);
	free(tmp);
	return (rt);
}

void	print_lst(t_app *app, t_lst_elem *lst)
{
	t_elem			*elm;

	elm = lst->first;
	while (elm)
	{
		if (app->color)
		{
			if (elm->stat.st_mode & 040000)
			ft_printf("{FG_CYAN}{BOLD}");
			else if (elm->stat.st_mode & 0111)
			ft_printf("{FG_RED}");
		}
		ft_printf("%-*s",lst->max_file_name, elm->name);
		if (app->color)
			ft_printf("{EOC}");
		if (elm->next)
			ft_putchar(' ');
		elm = elm->next;
	}
	ft_putchar('\n');
}

void			print_lst_list(t_app *app, t_lst_elem *lst)
{
	t_elem			*elm;
	unsigned int	size_len;

	lst->max_size = nbr_len(lst->max_size);
	elm = lst->first;
	ft_printf("total %d\n", lst->total);
	while (elm)
	{
		print_elem_list(app, elm, lst);
		elm = elm->next;
	}
}
