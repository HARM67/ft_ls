/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 21:45:22 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/17 07:28:14 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*r_itoa_8(long int nb, char *tmp)
{
	char	*rt;

	if (nb < 0)
	{
		*tmp = '-';
		r_itoa_8(-nb, tmp + 1);
		return (tmp);
	}
	else if (nb > 9)
	{
		rt = r_itoa_8(nb / 10, tmp);
		*rt = nb % 10 + '0';
		return (rt + 1);
	}
	else if (nb > 0)
		*tmp = nb + '0';
	return (tmp + 1);
}

char		*itoa_8(long int n)
{
	char tmp[21];
	char *rt;

	if (n < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	if (n == 0)
		return (ft_strdup("0"));
	ft_bzero(tmp, 21);
	r_itoa_8(n, tmp);
	rt = ft_strdup(tmp);
	return (rt);
}
