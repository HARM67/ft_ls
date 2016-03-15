/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 14:31:54 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/15 08:03:01 by mfroehly         ###   ########.fr       */
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

void	print_color_1(t_elem *elm)
{
	if ((elm->stat.st_mode & 0770000) == 0020000)
		ft_printf("{FG_BLUE}{BG_YELLOW}");
	else if ((elm->stat.st_mode & 0001000) == 0001000 &&
			(elm->stat.st_mode & 02))
		ft_printf("{FG_BLACK}{BG_GREEN}");
	else if (elm->stat.st_mode & 02)
		ft_printf("{FG_BLACK}{BG_YELLOW}");
	else if ((elm->stat.st_mode & 0770000) == 040000)
		ft_printf("{FG_CYAN}{BOLD}");
	else if ((elm->stat.st_mode & 0770000) == 0120000)
		ft_printf("{FG_PINK}");
	else if ((elm->stat.st_mode& 0770000) == 0140000)
		ft_printf("{FG_GREEN}");
	else if ((elm->stat.st_mode & 0770000) == 0010000)
		ft_printf("{FG_YELLOW}");
	else if (elm->stat.st_mode & 0111)
		ft_printf("{FG_RED}");
	else if ((elm->stat.st_mode & 0770000) == 0060000)
		ft_printf("{FG_BLUE}{BG_CYAN}");
	else if ((elm->stat.st_mode & 0006000) == 0004000)
		ft_printf("{FG_BLACK}{BG_RED}");
	else if ((elm->stat.st_mode & 0006000) == 0002000)
		ft_printf("{FG_BLACK}{BG_CYAN}");
}

void	print_name(t_app *app, t_lst_elem *lst, t_elem *elm)
{
	if (app->color)
	{
		print_color_1(elm);
	}
	ft_printf("%-*s", lst->max_file_name, elm->name);
	if (app->color)
		ft_printf("{EOC}");
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
		print_name(app, lst, elm);
		elm = (app->reverse_sort) ? elm->previous : elm->next;
		i++;
		if (nb_col && (i % nb_col) == 0)
			ft_putchar('\n');
		else if (elm)
			ft_putchar(' ');
	}
	if (app->recursive_depth)
		ft_putchar('\n');
}

void			print_lst_list(t_app *app, t_lst_elem *lst)
{
	t_elem			*elm;

	if (lst->have_periph)
		lst->max_size = 11111111;
	lst->max_size = nbr_len(lst->max_size);
	elm = (app->reverse_sort) ? lst->last : lst->first;
	if (!lst->no_total)
		ft_printf("total %d\n", lst->total);
	while (elm)
	{
		print_elem_list(app, elm, lst);
		elm = (app->reverse_sort) ? elm->previous : elm->next;
	}
}
