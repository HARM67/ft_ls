/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 22:08:19 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/08 02:43:49 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BUFF_SIZE 4096
# include "libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <inttypes.h>

typedef struct s_form	t_form;
typedef union u_arg		t_arg;

struct					s_form
{
	char				diese;
	char				zero;
	char				space;
	char				moin;
	char				plus;
	char				point;
	char				h_flag;
	char				l_flag;
	char				j_flag;
	char				z_flag;
	int					longueur;
	size_t				precision;
	char				signe;
	char				base;
	unsigned long		size;
	char				maj;
	char				letter;
	char				positive;
	char				*devant;
	unsigned long int	length;
	unsigned long int	total_length;
};

union					u_arg
{
	char				c;
	int					i;
	long int			li;
	unsigned int		uli;
};

int						ft_sprintf(char **rt, const char *fmt, ...);
int						ft_fprintf(int fd, const char *fmt, ...);
int						ft_printf(const char *fmt, ...);
int						printf_loop(const char *fmt, char **str, va_list *list);

char					*uitoa_base_1(unsigned char n, int base);
char					*uitoa_base_2(unsigned short int n, int base);
char					*uitoa_base_4(unsigned int n, int base);
char					*uitoa_base_8(unsigned long int n, int base);

char					*itoa_1(char n);
char					*itoa_2(short int n);
char					*itoa_4(int n);
char					*itoa_8(long int n);

void					insert_flag(char **str, t_form *form);

char					*make_longueur(t_form *form);
void					make_devant(t_form *form);
void					make_precision(char **str, t_form *form);
void					make_flagstr(char **str, t_form *form, char *longueur);

char					*argtoa(t_form *form, va_list *list);

void					read_flag(const char **fmt,
										t_form *form, va_list *list);

void					read_longueur(const char **fmt,
										t_form *form, va_list *list);
void					set_size(t_form *form);
void					normalize_flag(t_form *form);
char					is_flag(char c);
void					read_precision(const char **fmt,
										t_form *form, va_list *list);

char					*print_arg(const char **fmt, va_list *list, int *l);

char					*itounicode(unsigned int u);
char					*ltostr(int *l, int l_max);
char					*ft_strncon(char **s1, char **s2, size_t l, int flag);

char					*ftoa(double n, int precision);

char					*stoa(t_form *form, va_list *list);
char					*n_base(t_form *form, va_list *list);
void					make_color(const char **fmt, char **str, int *l);
#endif
