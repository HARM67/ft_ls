/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 14:37:22 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/21 19:31:04 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	write_attribut(t_elem *elm)
{
	char	*path;

	if ((elm->stat.st_mode & 0770000) == 0120000)
		path = elm->link_path;
	else
		path = elm->path;
	if (listxattr(path, 0, 0, 0) > 0)
		ft_printf("@");
	else
		ft_printf(" ");
}

void		print_date(time_t elm_time)
{
	unsigned int	i;
	char			*date;

	date = ctime(&elm_time);
	i = 3;
	if ((time(0) - elm_time) < 15552000)
		while (++i <= 15)
			ft_putchar(date[i]);
	else
	{
		while (++i <= 10)
			ft_putchar(date[i]);
		i = 18;
		while (++i <= 23)
			ft_putchar(date[i]);
	}
}

void		print_elem_list_3(t_lst_elem *lst, t_elem *elm)
{
	ft_printf(" %*d %-*s  %-*s  %*d ",
		nbr_len(lst->max_nlink), elm->stat.st_nlink,
		lst->max_name_len, elm->user_name,
		lst->max_grp_len, elm->groupe_name,
		lst->max_size, elm->stat.st_size);
}

void		print_elem_list_2(t_lst_elem *lst, t_elem *elm)
{
	ft_printf(" %*d %-*s  %-*s %4d,%4d ",
		nbr_len(lst->max_nlink), elm->stat.st_nlink,
		lst->max_name_len, elm->user_name,
		lst->max_grp_len, elm->groupe_name,
		(elm->stat.st_rdev & 0xff000000) >> 24,
		elm->stat.st_rdev & 0xffffff);
}

void		print_elem_list(t_app *app, t_elem *elm, t_lst_elem *lst)
{
	char buf[256];

	if (elm->rt_lstat == -1)
	{
		ft_printf("ft_ls: %s: Permission denied\n", elm->name);
		return ;
	}
	ft_bzero(buf, 256);
	write_mode(elm->stat.st_mode);
	write_attribut(elm);
	if ((elm->stat.st_mode & 0770000) == 0060000 ||
			(elm->stat.st_mode & 0770000) == 0020000)
		print_elem_list_2(lst, elm);
	else
		print_elem_list_3(lst, elm);
	print_date(elm->stat.st_mtimespec.tv_sec);
	ft_putchar(' ');
	lst->max_file_name = 0;
	print_name(app, lst, elm);
	if ((elm->stat.st_mode & 0770000) == 0120000)
	{
		readlink(elm->path, buf, 256);
		ft_printf(" -> %s", buf);
	}
	ft_putchar('\n');
}
