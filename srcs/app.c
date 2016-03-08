#include "ft_ls.h"

void	init_app(t_app *app)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	app->row = w.ws_row;
	app->col = w.ws_col;
}

void	run_app(t_app *app)
{
	push_path(app, "/");
	parcour(app);
}
