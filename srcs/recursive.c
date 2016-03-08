#include "ft_ls.h"

void	parcour(t_app *app)
{
	DIR				*dirp;
	struct dirent	*d;
	char			*path;
	t_lst_elem		lst;
	t_elem			*tmp;

	path = path_str(app, 1);
	dirp = opendir(path);
	if (dirp == 0)
	{
		free(path);
		return ;
	}
	ft_bzero(&lst, sizeof(t_lst_elem));
	ft_printf("%s\n",path);
	free(path);
	while ((d = readdir(dirp)))
		insert_elm(app, &lst, d);
	print_lst(&lst);
	tmp = lst.first;
	if (app->recursive)
		while (tmp)
		{
			push_path(app, tmp->name);
			if ((tmp->stat.st_mode & 0040000) && tmp->name[0] != '.')
				parcour(app);
			pop_path(app);
			tmp = tmp->next;
		}
	clean_lst(&lst);
	closedir(dirp);
	free(d);
}
