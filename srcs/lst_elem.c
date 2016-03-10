/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 14:31:54 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/10 21:16:15 by mfroehly         ###   ########.fr       */
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
	unsigned int	i;
	unsigned int	nb_col;
	t_elem			*elm;

	elm = (app->reverse_sort) ? lst->last : lst->first;
	i = 0;
	nb_col = app->col / (lst->max_file_name + 1);
	while (elm)
	{
		if (app->color)
		{
			if (elm->stat.st_mode & 040000)
				ft_printf("{FG_CYAN}{BOLD}");
			else if (elm->stat.st_mode & 0111)
			{
				if ((elm->stat.st_mode & 0120000) == 0120000)
					ft_printf("{FG_PINK}");
				else
					ft_printf("{FG_RED}");
			}
		}
		ft_printf("%-*s", lst->max_file_name, elm->name);
		if (app->color)
			ft_printf("{EOC}");
		elm = (app->reverse_sort) ? elm->previous : elm->next;
		i++;
		if ((i % nb_col) == 0)
			ft_putchar('\n');
		else if (elm)
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

void			print_lst_list(t_app *app, t_lst_elem *lst)
{
	t_elem			*elm;

	lst->max_size = nbr_len(lst->max_size);
	elm = (app->reverse_sort) ? lst->last : lst->first;
	ft_printf("total %d\n", lst->total);
	while (elm)
	{
		print_elem_list(app, elm, lst);
		elm = (app->reverse_sort) ? elm->previous : elm->next;
	}
}
