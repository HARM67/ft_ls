/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 21:47:16 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/17 16:26:44 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_sprintf(char **rt, const char *fmt, ...)
{
	int		l;
	va_list	list;
	char	*str;

	if (fmt == 0)
		return (0);
	str = 0;
	*rt = 0;
	va_start(list, fmt);
	l = printf_loop(fmt, &str, &list);
	va_end(list);
	if (str != 0)
		*rt = str;
	return (l);
}

int	ft_fprintf(int fd, const char *fmt, ...)
{
	int		l;
	va_list	list;
	char	*str;

	if (fmt == 0)
		return (0);
	str = 0;
	va_start(list, fmt);
	l = printf_loop(fmt, &str, &list);
	va_end(list);
	if (str != 0)
	{
		write(fd, str, l);
		free(str);
	}
	return (l);
}

int	ft_printf(const char *fmt, ...)
{
	int		l;
	va_list	list;
	char	*str;

	if (fmt == 0)
		return (0);
	str = 0;
	va_start(list, fmt);
	l = printf_loop(fmt, &str, &list);
	va_end(list);
	if (str != 0)
	{
		write(1, str, l);
		free(str);
	}
	return (l);
}
