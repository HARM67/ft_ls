#include "ft_ls.h"

void	init_app(t_app *app)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	app->row = w.ws_row;
	app->col = w.ws_col;
	app->compare = *compare_ascii;
	app->print = *print_lst_list;
	app->reverse_sort = 0;
	app->show_hidden = 0;
	app->recursive = 0;
	app->color = 1;
}

void	run_app(t_app *app)
{
	if (app->ac == 1)
		push_path(app, ".");
	else
		push_path(app, app->av[1]);
	parcour(app);
}
