/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 11:48:48 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/08 02:35:29 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_this(char **p, char *search, int size)
{
	if (ft_strncmp(*p, search, size) == 0)
	{
		(*p) += size;
		return (1);
	}
	return (0);
}

static char	*decode_color(char **p, int type)
{
	int color;

	(*p) += 3;
	if (is_this(p, "BLACK", 5))
		color = 0;
	else if (is_this(p, "RED", 3))
		color = 1;
	else if (is_this(p, "GREEN", 5))
		color = 2;
	else if (is_this(p, "YELLOW", 6))
		color = 3;
	else if (is_this(p, "BLUE", 4))
		color = 4;
	else if (is_this(p, "PINK", 4))
		color = 5;
	else if (is_this(p, "CYAN", 4))
		color = 6;
	else if (is_this(p, "GREY", 4))
		color = 7;
	else
		return (ft_strdup("{"));
	return (ft_itoa(color + type));
}

static char	*decode_type(char **p)
{
	if (ft_strncmp(*p, "FG_", 3) == 0)
		return (decode_color(p, 30));
	else if (ft_strncmp(*p, "BG_", 3) == 0)
		return (decode_color(p, 40));
	else if (is_this(p, "EOC", 3))
		return (ft_strdup("0"));
	else if (is_this(p, "BOLD", 4))
		return (ft_strdup("1"));
	else if (is_this(p, "DARK", 4))
		return (ft_strdup("2"));
	else if (is_this(p, "ITALIC", 6))
		return (ft_strdup("3"));
	else if (is_this(p, "UNDERLINE", 9))
		return (ft_strdup("4"));
	else if (is_this(p, "FLASH", 5))
		return (ft_strdup("5"));
	else if (is_this(p, "HIGHLIGHT", 9))
		return (ft_strdup("7"));
	return (ft_strdup("{"));
}

void		create_str_color(char **tmp)
{
	char *tmp2;

	tmp2 = ft_strdup("\033[");
	ft_strncon(&tmp2, tmp, 0, 0x2 | 0x8 | 0x20 | 0x1 | 0x4);
	tmp2 = ft_strdup("m");
	ft_strncon(tmp, &tmp2, 0, 0x1 | 0x4 | 0x10 | 0x2 | 0x8);
}

void		make_color(const char **fmt, char **str, int *l)
{
	char	*p;
	char	*tmp;
	int		i;

	i = 0;
	p = (char *)*fmt;
	p++;
	while (*p != 0 && *p == ' ')
		p++;
	tmp = decode_type(&p);
	while (*p != 0 && *p == ' ')
		p++;
	if (*tmp == '{' || *p != '}')
	{
		i = (*l)++;
		(*fmt)++;
		ft_strncon(str, &tmp, i, 0x40 | 0x1 | 0x4 | 0x2 | 0x8 | 0x10);
		return ;
	}
	create_str_color(&tmp);
	p++;
	(*fmt) = p;
	i = *l;
	*l += ft_strlen(tmp);
	ft_strncon(str, &tmp, i, 0x40 | 0x1 | 0x4 | 0x2 | 0x8 | 0x10);
}
