#include "ft_ls.h"

void	read_stat(t_elem *elm)
{
	stat(elm->path, &elm->stat);
}

