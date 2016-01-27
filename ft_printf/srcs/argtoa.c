/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argtoa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 21:52:17 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/08 02:45:06 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*uinttoa_base(t_form *form, va_list *list)
{
	unsigned long int	tmp;

	tmp = (unsigned long int)va_arg(*list, unsigned long int);
	if (((form->letter == 'o' || form->letter == 'O')
				&& tmp == 0 && form->point == 0)
			|| ((form->letter == 'x' || form->letter == 'X') && tmp == 0))
		form->diese = 0;
	if (form->size == 8 || form->letter == 'O' || form->letter == 'U' ||
			form->letter == 'p' || form->letter == 'B')
		return (uitoa_base_8(tmp, form->base));
	else if (form->size == 1)
		return (uitoa_base_1((unsigned char)tmp, form->base));
	else if (form->size == 2)
		return (uitoa_base_2((unsigned short int)tmp, form->base));
	else if (form->size == 4)
		return (uitoa_base_4((unsigned int)tmp, form->base));
	return (0);
}

static char	*inttoa(t_form *form, va_list *list)
{
	long int tmp;

	tmp = (long int)va_arg(*list, long int);
	if (form->size == 8 || ft_isupper(form->letter))
		return (itoa_8(tmp));
	else if (form->size == 1)
		return (itoa_8((char)tmp));
	else if (form->size == 2)
		return (itoa_8((short int)tmp));
	else if (form->size == 4)
		return (itoa_8((int)tmp));
	return (0);
}

static void	arg_conform(t_form *form, char **rt)
{
	if ((form->letter == 'c' || form->letter == 'C') && **rt == '\0')
		form->length = 1;
	else
		form->length = ft_strlen(*rt);
	if ((form->signe == 0 || form->signe == 1 || form->signe == -6)
			&& **rt == '-')
	{
		form->length--;
	}
	if ((form->signe == 0 || form->signe == 1) && form->point && **rt == '0')
	{
		free(*rt);
		*rt = ft_strdup("\0");
		form->length = 0;
	}
}

char		*argtoa(t_form *form, va_list *list)
{
	char *rt;

	rt = 0;
	if (form->signe >= -5 && form->signe < 0)
		rt = stoa(form, list);
	else if (form->signe == 0)
		rt = uinttoa_base(form, list);
	else if (form->signe == 1)
		rt = inttoa(form, list);
	else if (form->signe == -6)
		rt = ftoa(va_arg(*list, double), 6);
	else if (form->signe == -7)
		return (n_base(form, list));
	arg_conform(form, &rt);
	return (rt);
}
