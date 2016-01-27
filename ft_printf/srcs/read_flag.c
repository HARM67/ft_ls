/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 22:05:36 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/17 07:46:06 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	read_flag_size(const char **fmt, t_form *form)
{
	if (**fmt == 'l')
		form->l_flag++;
	else if (**fmt == 'j')
		form->j_flag++;
	else if (**fmt == 'h')
		form->h_flag++;
	else if (**fmt == 'z')
		form->z_flag++;
}

void		read_flag(const char **fmt, t_form *form, va_list *list)
{
	while (is_flag(**fmt))
	{
		if (**fmt == '#')
			form->diese = 1;
		else if (**fmt == '0')
			form->zero = 1;
		else if (**fmt == ' ')
			form->space = 1;
		else if (**fmt == '-')
			form->moin = 1;
		else if (**fmt == '+')
			form->plus = 1;
		else if (**fmt == '.')
			read_precision(fmt, form, list);
		else if (ft_isdigit(**fmt) || **fmt == '*')
			read_longueur(fmt, form, list);
		else
			read_flag_size(fmt, form);
		(*fmt)++;
	}
}
