#include "ft_ls.h"

void	init_app(t_app *app)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	app->row = w.ws_row;
	app->col = w.ws_col;
	app->compare = *compare_ascii;
	app->reverse_sort = 0;
}

void	run_app(t_app *app)
{
	if (app->ac == 1)
		push_path(app, ".");
	else
		push_path(app, app->av[1]);
	parcour(app);
}
