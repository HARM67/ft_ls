/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 21:45:24 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/11 21:45:27 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*r_itoa_1(char nb, char *tmp)
{
	char	*rt;

	if (nb < 0)
	{
		*tmp = '-';
		r_itoa_1(-nb, tmp + 1);
		return (tmp);
	}
	else if (nb > 9)
	{
		rt = r_itoa_1(nb / 10, tmp);
		*rt = nb % 10 + '0';
		return (rt + 1);
	}
	else if (nb > 0)
		*tmp = nb + '0';
	return (tmp + 1);
}

char		*itoa_1(char n)
{
	char tmp[5];
	char *rt;

	if (n == -128)
		return (ft_strdup("-128"));
	if (n == 0)
		return (ft_strdup("0"));
	ft_bzero(tmp, 5);
	r_itoa_1(n, tmp);
	rt = ft_strdup(tmp);
	return (rt);
}
