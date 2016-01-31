#include "ft_ls.h"

void	parcour(t_app *app)
{
	DIR				*dirp;
	struct dirent	*d;
	char			*path;
	t_lst_elem		lst;

	path = path_str(app, 1);
	dirp = opendir(path);
	if (dirp == 0)
		return ;
	ft_bzero(&lst, sizeof(t_lst_elem));
	ft_printf("%s\n",path);
	while ((d = readdir(dirp)))
		push_elem(app, &lst, d);
	print_lst(&lst);
	while (lst.first)
	{
		push_path(app, lst.first->name);
		if (lst.first->type == 4 && lst.first->name[0] != '.')
			parcour(app);
		pop_path(app);
		lst.first = lst.first->next;
	}
	closedir(dirp);
	free(d);
	clean_lst(&lst);
	free(path);
			}
