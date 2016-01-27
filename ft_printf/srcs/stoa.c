/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 07:52:38 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/17 08:05:21 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ctoa(t_form *form, va_list *list)
{
	char	c[5];

	ft_bzero(c, 5);
	if (form->signe == -1)
	{
		c[0] = va_arg(*list, int);
		return (ft_strdup(c));
	}
	else if (form->signe == -3)
	{
		c[0] = form->letter;
		form->letter = 'c';
		return (ft_strdup(c));
	}
	else if (form->signe == -4)
		return (itounicode((int)va_arg(*list, int)));
	return (0);
}

static char	*strtoa(t_form *form, va_list *list)
{
	char *p;

	p = 0;
	p = va_arg(*list, char *);
	if (p != 0)
	{
		p = ft_strdup(p);
		if (form->point && (ft_strlen(p) > form->precision))
			p[form->precision] = '\0';
	}
	else if (form->point == 0)
		p = ft_strdup("(null)");
	else
		p = ft_strdup("\0");
	return (p);
}

static char	*lstrtoa(t_form *form, va_list *list)
{
	int		*i;

	i = 0;
	i = va_arg(*list, int *);
	if (i != 0)
		return (ltostr(i, (form->point) ? (int)form->precision : -1));
	else if (form->point == 0)
		return (ft_strdup("(null)"));
	else
		return (ft_strdup("\0"));
}

char		*stoa(t_form *form, va_list *list)
{
	if (form->signe == -2)
		return (strtoa(form, list));
	else if (form->signe == -5)
		return (lstrtoa(form, list));
	return (ctoa(form, list));
}
