/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 21:54:21 by mfroehly          #+#    #+#             */
/*   Updated: 2015/12/17 08:52:17 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	retirer_signe(char **str, t_form *form)
{
	char *tmp;

	if (**str != '-' || form->letter == 'c' || form->letter == 'C' ||
			form->letter == 's' || form->letter == 'S')
	{
		form->positive = 1;
		return ;
	}
	tmp = ft_strdup((*str) + 1);
	free(*str);
	*str = tmp;
}

void		insert_flag(char **str, t_form *form)
{
	char	*longueur;

	retirer_signe(str, form);
	make_devant(form);
	if (form->signe >= 0)
		make_precision(str, form);
	longueur = make_longueur(form);
	if (form->devant != 0)
		form->length += ft_strlen(form->devant);
	make_flagstr(str, form, longueur);
	form->length += ft_strlen(longueur);
	if (form->devant)
		free(form->devant);
	if (longueur)
		free(longueur);
}
