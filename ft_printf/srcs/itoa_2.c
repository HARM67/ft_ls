/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 21:45:26 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/11 21:45:27 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*r_itoa_2(short nb, char *tmp)
{
	char	*rt;

	if (nb < 0)
	{
		*tmp = '-';
		r_itoa_2(-nb, tmp + 1);
		return (tmp);
	}
	else if (nb > 9)
	{
		rt = r_itoa_2(nb / 10, tmp);
		*rt = nb % 10 + '0';
		return (rt + 1);
	}
	else if (nb > 0)
		*tmp = nb + '0';
	return (tmp + 1);
}

char		*itoa_2(short int n)
{
	char tmp[7];
	char *rt;

	if (n == -32768)
		return (ft_strdup("-32768"));
	if (n == 0)
		return (ft_strdup("0"));
	ft_bzero(tmp, 7);
	r_itoa_2(n, tmp);
	rt = ft_strdup(tmp);
	return (rt);
}
