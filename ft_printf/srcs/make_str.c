/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 08:14:51 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/17 08:52:13 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*make_longueur(t_form *form)
{
	int		len;
	char	*tmp;

	len = form->length;
	if (form->devant != 0)
		len += ft_strlen(form->devant);
	if (len >= form->longueur)
		return (ft_strdup("\0"));
	tmp = ft_memalloc(form->longueur - len + 1);
	if (form->zero && form->moin == 0 && (form->point == 0 || form->signe < 0))
		ft_memset(tmp, '0', form->longueur - len);
	else
		ft_memset(tmp, ' ', form->longueur - len);
	return (tmp);
}

void	make_devant(t_form *form)
{
	if (form->letter == 'c' || form->letter == 's' || form->letter == 'C' ||
		form->letter == 'S')
		return ;
	if (form->positive == 0)
		form->devant = ft_strdup("-");
	else if (form->plus && form->signe && form->positive)
		form->devant = ft_strdup("+");
	else if (form->space && form->signe)
		form->devant = ft_strdup(" ");
	else if (form->diese && (form->letter == 'o' || form->letter == 'O')
			&& !(form->point && form->precision != 0))
		form->devant = ft_strdup("0");
	else if ((form->diese && (form->letter == 'x' || form->letter == 'X')) ||
		form->letter == 'p')
		form->devant = ft_strdup("0x");
	else
		form->devant = 0;
}

void	make_precision(char **str, t_form *form)
{
	size_t	len;
	char	*tmp;
	int		i;

	len = form->length;
	if (len >= form->precision || form->point == 0)
		return ;
	tmp = ft_memalloc(form->precision + 1);
	ft_memset(tmp, '0', form->precision);
	i = 0;
	while ((unsigned int)i < len)
	{
		tmp[form->precision + i - len] = (*str)[i];
		i++;
	}
	form->length = form->precision;
	free(*str);
	*str = tmp;
}

void	make_flagstr(char **str, t_form *form, char *longueur)
{
	char *tmp;

	if (form->zero && form->moin == 0)
	{
		tmp = ft_strncon(&longueur, str, 0, 0x2 | 0x8);
		if (form->devant)
			ft_strncon(&form->devant, &tmp, 0, 0x2 | 0x8 | 0x20);
		*str = tmp;
	}
	else
	{
		if (form->devant)
			tmp = ft_strncon(&form->devant, str, 0, 0x2 | 0x8);
		else
			tmp = *str;
		if (form->zero == 0 && form->moin == 0)
			ft_strncon(&longueur, &tmp, form->length, 0x80 | 0x8 | 0x20 | 0x2);
		else
			ft_strncon(&tmp, &longueur, form->length, 0x40 | 0x4 | 0x10 | 0x1);
		*str = tmp;
	}
}
