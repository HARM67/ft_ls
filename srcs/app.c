#include "ft_ls.h"

void	init_app(t_app *app)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	app->row = w.ws_row;
	app->col = w.ws_col;
	app->compare = *compare_ascii;
	app->print = *print_lst;
}

void	check_invalide(t_app *app)
{
	DIR		*dirp;
	t_p_arg	*tmp;

	tmp = app->first_p_arg;
	while (tmp)
	{
		dirp = opendir(tmp->path);
		if (dirp == 0)
			ft_printf("ft_ls: %s: No such file or directory\n", tmp->path);
		tmp = tmp->next;
	}
}

void	run_app(t_app *app)
{
	t_p_arg	*tmp;

	read_arg(app);
	tmp = app->first_p_arg;
	check_invalide(app);
	while (tmp)
	{
		push_path(app, tmp->path);
		parcour(app);
		pop_path(app);
		tmp = tmp->next;
	}
	/*
	if (app->ac == 1)
		push_path(app, ".");
	else
		push_path(app, app->av[1]);
	*/
	//parcour(app);
}
