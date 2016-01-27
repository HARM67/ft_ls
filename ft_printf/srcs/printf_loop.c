/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 09:21:51 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/08 02:36:02 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	recup_arg(const char **fmt, va_list *list, char **str, int *l)
{
	int		i;
	char	*tmp;

	i = *l;
	tmp = print_arg(fmt, list, l);
	ft_strncon(str, &tmp, i, 0x40 | 0x1 | 0x4 | 0x2 | 0x8 | 0x10);
}

static void	print_pourcent(const char **fmt, char **str, int *l)
{
	char	*tmp;

	tmp = ft_strdup("%");
	ft_strncon(str, &tmp, *l, 0x40 | 0x1 | 0x4 | 0x2 | 0x8 | 0x10);
	(*l)++;
	(*fmt) += 2;
}

static void	print_character(const char **fmt, char **str, int *l)
{
	char	*tmp;

	tmp = (char*)*fmt;
	ft_strncon(str, &tmp, *l, 0x40 | 0x1 | 0x4 | 0x10);
	(*l)++;
	(*fmt)++;
}

int			printf_loop(const char *fmt, char **str, va_list *list)
{
	int		l;

	l = 0;
	while (*fmt != 0)
	{
		if (*fmt == '%' && *(fmt + 1) != '%')
			recup_arg(&fmt, list, str, &l);
		else if (*fmt == '%' && *(fmt + 1) == '%')
			print_pourcent(&fmt, str, &l);
		else if (*fmt == '{')
			make_color(&fmt, str, &l);
		else
			print_character(&fmt, str, &l);
	}
	return (l);
}
