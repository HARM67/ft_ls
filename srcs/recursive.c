#include "ft_ls.h"

void	parcour(t_app *app)
{
	DIR				*dirp;
	struct dirent	*d;
	char			*path;
	t_lst_elem		lst;

	path = path_str(app);
	dirp = opendir(path);
	ft_bzero(&lst, sizeof(t_lst_elem));
		ft_printf("%s\n",path);
	while ((d = readdir(dirp)))
	{
		ft_printf("\t%s\n", d->d_name);
		push_elem(&lst, d);
	}
	ft_printf("\n");
	while (lst.first)
	{
		if (lst.first->type == 4 && lst.first->name[0] != '.')
		{
			push_path(app, lst.first->name);
			parcour(app);
			pop_path(app);
		}
		lst.first = lst.first->next;
	}
	free(path);
}
