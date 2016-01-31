#include "ft_ls.h"

static void	write_file_type(mode_t mode)
{
	if (mode & 0010000)
		ft_putchar('p');
	else if (mode & 0020000)
		ft_putchar('c');
	else if (mode & 0040000)
		ft_putchar('d');
	else if (mode & 0060000)
		ft_putchar('b');
	else if (mode & 0100000)
		ft_putchar('-');
	else if (mode & 0120000)
		ft_putchar('l');
	else if (mode & 0140000)
		ft_putchar('s');
}

static void	write_mode_user(mode_t mode)
{
	if (mode & 0000400)
		ft_putchar('r');
	else
		ft_putchar('-');
	if (mode & 0000200)
		ft_putchar('w');
	else
		ft_putchar('-');
	if (mode & 0000100)
		ft_putchar('x');
	else
		ft_putchar('-');
}

static void	write_mode_group(mode_t mode)
{
	if (mode & 0000040)
		ft_putchar('r');
	else
		ft_putchar('-');
	if (mode & 0000020)
		ft_putchar('w');
	else
		ft_putchar('-');
	if (mode & 0000010)
		ft_putchar('x');
	else
		ft_putchar('-');
}

static void	write_mode_other(mode_t mode)
{
	if (mode & 0000004)
		ft_putchar('r');
	else
		ft_putchar('-');
	if (mode & 0000002)
		ft_putchar('w');
	else
		ft_putchar('-');
	if (mode & 0000001)
		ft_putchar('x');
	else
		ft_putchar('-');
}

void	write_mode(mode_t mode)
{
	write_file_type(mode);
	write_mode_user(mode);
	write_mode_group(mode);
	write_mode_other(mode);
}
