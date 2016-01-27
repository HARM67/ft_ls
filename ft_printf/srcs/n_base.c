/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_base.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 11:18:41 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/17 15:38:43 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*n_base(t_form *form, va_list *list)
{
	int	*i;

	i = va_arg(*list, int *);
	*i = form->total_length;
	form->length = 0;
	return (ft_strdup("\0"));
}
