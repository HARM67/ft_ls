/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 08:21:51 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/08 02:45:19 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	sizeofunicode(int u)
{
	if (u < 128)
		return (1);
	else if (u < 2048)
		return (2);
	else if (u < 65536)
		return (3);
	return (4);
}

static int	strwlen(int *u)
{
	int i;

	i = 0;
	while (*u != 0)
	{
		i += sizeofunicode(*u);
		u++;
	}
	return (i);
}

char		*itounicode(unsigned int u)
{
	char rt[5];

	ft_bzero(rt, 5);
	if (u < 128)
		rt[0] = u;
	else if (u < 2048)
	{
		rt[0] = 0xC0 + ((u >> 6) & 0x1F);
		rt[1] = 0x80 + (u & 0x3F);
	}
	else if (u < 65536)
	{
		rt[0] = 0xE0 + ((u >> 12) & 0xF);
		rt[1] = 0x80 + ((u >> 6) & 0x3F);
		rt[2] = 0x80 + (u & 0x3F);
	}
	else
	{
		rt[0] = 0xF0 + ((u >> 18) & 0xF);
		rt[1] = 0x80 + ((u >> 12) & 0x3F);
		rt[2] = 0x80 + ((u >> 6) & 0x3F);
		rt[3] = 0x80 + (u & 0x7);
	}
	return (ft_strdup(rt));
}

char		*ltostr(int *l, int l_max)
{
	char	*str;
	int		i;
	char	*tmp;

	i = (l_max == -1) ? strwlen(l) : l_max;
	str = (char*)malloc(i + 1);
	ft_bzero(str, i);
	while (*l && i > sizeofunicode(*l) - 1)
	{
		i -= sizeofunicode(*l);
		tmp = itounicode(*l++);
		ft_strcat(str, tmp);
		free(tmp);
	}
	return (str);
}
