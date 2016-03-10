#include "ft_ls.h"

void	parcour(t_app *app)
{
	DIR				*dirp;
	struct dirent	*d;
	static int		temoin = 0;
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
	if (temoin)
		ft_putchar('\n');
	++temoin;
	if (app->recursive_depth)
		ft_printf("%s:\n",path);
	app->recursive_depth++;
	free(path);
	while ((d = readdir(dirp)))
		insert_elm(app, &lst, d);
	app->print(app, &lst);
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
	app->recursive_depth--;
}
