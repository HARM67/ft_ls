/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uitoa_base_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 21:43:32 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/17 08:55:18 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*r_ftoae(double nb, char *tmp, int precision)
{
	char	*rt;

	if (nb < 0.0)
	{
		*tmp = '-';
		r_ftoae(-nb, tmp + 1, precision);
		return (tmp);
	}
	else if (nb >= 10.0)
	{
		rt = r_ftoae(nb / 10.0, tmp, precision);
		*rt = ((long int)nb % 10) + '0';
		return (rt + 1);
	}
	else if ((long int)nb > 0)
		*tmp = (long int)nb + '0';
	return (tmp + 1);
}

static void	r_ftoai(double nb, char *tmp, int precision)
{
	int i;

	if (nb < 0.0)
		nb = -nb;
	i = 1;
	tmp[0] = '.';
	while (i < precision)
	{
		nb *= 10.0;
		if ((long int)nb % 10 >= 0 && (long int)nb % 10 <= 9)
			tmp[i++] = (long int)nb % 10 + '0';
		else
			tmp[i++] = '0';
	}
}

static void	make_fprecision(char *str, int precision)
{
	if (str[precision + 1] >= '5')
	{
		str[precision]++;
	}
	str[precision + 1] = '\0';
}

char		*ftoa(double n, int precision)
{
	char	tmp[50];
	char	tmp2[precision + 2];
	char	*rt;

	if (n == 0)
		return (ft_strdup("0.0"));
	ft_bzero(tmp, 50);
	ft_bzero(tmp2, precision + 2);
	r_ftoae(n, tmp, precision + 1);
	r_ftoai(n, tmp2, precision + 1);
	make_fprecision(tmp2, precision);
	rt = ft_strjoin(tmp, tmp2);
	return (rt);
}
