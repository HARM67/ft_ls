#include "ft_ls.h"

int main(int ac, char **av)
{
	t_app	app;

	ft_bzero(&app, sizeof(t_app));
	app.ac = ac;
	app.av = av;
	init_app(&app);
	run_app(&app);
	while (1);
	return (0);
}
