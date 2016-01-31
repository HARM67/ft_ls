#include "ft_ls.h"

static unsigned int	nbr_len(unsigned int nbr)
{
	unsigned int	rt;
	char			*tmp;

	tmp = uitoa_base_4(nbr, 10);
	rt = ft_strlen(tmp);
	free(tmp);
	return (rt);
}

void				print_lst(t_lst_elem *lst)
{
	t_elem			*elm;
	unsigned int	size_len;

	lst->max_size = nbr_len(lst->max_size);
	elm = lst->first;
	while (elm)
	{
		print_elem(elm, lst);
		elm = elm->next;
	}
	ft_putchar('\n');
}
