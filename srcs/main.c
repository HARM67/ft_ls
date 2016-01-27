#include "ft_ls.h"

int main(int ac, char **av)
{
	t_app	app;
	app.ac = ac;
	app.av = av;
	init_app(&app);
	run_app(&app);
	return (0);
}
