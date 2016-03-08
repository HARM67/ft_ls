#include "ft_ls.h"

void	read_stat(t_elem *elm)
{
	lstat(elm->path, &elm->stat);
}

