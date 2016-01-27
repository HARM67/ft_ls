/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 16:13:16 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/17 08:54:36 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strncon(char **s1, char **s2, size_t l, int flag)
{
	char	*rt;
	int		l_s1;
	int		l_s2;

	l_s1 = (flag & 0x40) ? l : ft_strlen(*s1);
	l_s2 = (flag & 0x80) ? l : ft_strlen(*s2);
	rt = ft_memalloc(sizeof(char) * (l_s1 + l_s2 + 1));
	if (rt == 0)
		return (0);
	ft_memcpy(rt, *s1, l_s1);
	ft_memcpy(rt + l_s1, *s2, l_s2);
	(flag & 0x4) ? ft_bzero(*s1, l_s1) : 0;
	(flag & 0x8) ? ft_bzero(*s2, l_s2) : 0;
	(flag & 0x1) ? free(*s1) : 0;
	(flag & 0x2) ? free(*s2) : 0;
	*s1 = (flag & 0x10) ? rt : *s1;
	*s2 = (flag & 0x20) ? rt : *s2;
	return (rt);
}
