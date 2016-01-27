/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 22:06:37 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/17 15:44:14 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	read_base_character(const char **fmt, t_form *form)
{
	if (**fmt == 'c' && form->l_flag == 0)
		form->signe = -1;
	else if (**fmt == 'C' || (**fmt == 'c' && form->l_flag))
		form->signe = -4;
	else if (**fmt == 's' && form->l_flag == 0)
		form->signe = -2;
	else if (**fmt == 'S' || (**fmt == 's' && form->l_flag))
		form->signe = -5;
	else
		form->signe = -3;
}

static	void	read_base_nbr(const char **fmt, t_form *form)
{
	form->letter = **fmt;
	if (**fmt == 'i' || **fmt == 'd' || **fmt == 'D')
	{
		form->signe = 1;
		form->base = 10;
	}
	else if (**fmt == 'u' || **fmt == 'U')
		form->base = 10;
	else if (**fmt == 'o' || **fmt == 'O')
		form->base = 8;
	else if (**fmt == 'x' || **fmt == 'X' || **fmt == 'p')
		form->base = 16;
	else if (**fmt == 'f' || **fmt == 'F')
		form->signe = -6;
	else if (**fmt == 'n')
		form->signe = -7;
	else if (**fmt == 'b' || **fmt == 'B')
		form->base = 2;
	else
		read_base_character(fmt, form);
	(*fmt)++;
}

void			make_x(char *str)
{
	while (*str != '\0')
	{
		if (ft_islower(*str))
			*str -= 32;
		str++;
	}
}

char			*print_arg(const char **fmt, va_list *list, int *l)
{
	t_form	form;
	char	*str;

	(*fmt)++;
	if ((**fmt) == '\0')
		return (ft_strdup("\0"));
	ft_bzero(&form, sizeof(t_form));
	form.total_length = *l;
	read_flag(fmt, &form, list);
	normalize_flag(&form);
	set_size(&form);
	read_base_nbr(fmt, &form);
	str = argtoa(&form, list);
	insert_flag(&str, &form);
	if (form.letter == 'X')
		make_x(str);
	*l += form.length;
	return (str);
}
