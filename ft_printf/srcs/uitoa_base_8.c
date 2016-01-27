/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uitoa_base_8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 21:42:30 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/12 07:43:48 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	itoc(int i)
{
	if (i >= 0 && i <= 9)
		return ((char)i + '0');
	return ((char)i + 'a' - 10);
}

static char	*r_uitoa(unsigned long int nb, char *tmp, int base)
{
	char	*rt;

	if (nb > (unsigned long int)base - 1)
	{
		rt = r_uitoa(nb / base, tmp, base);
		*rt = itoc(nb % base);
		return (rt + 1);
	}
	else if (nb > 0)
		*tmp = itoc(nb);
	return (tmp + 1);
}

char		*uitoa_base_8(unsigned long int n, int base)
{
	char tmp[65];
	char *rt;

	if (n == 0)
		return (ft_strdup("0"));
	ft_bzero(tmp, 65);
	r_uitoa(n, tmp, base);
	rt = ft_strdup(tmp);
	return (rt);
}
