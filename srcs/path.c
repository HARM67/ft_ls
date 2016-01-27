#include "ft_ls.h"

t_path	*new_path(char *str)
{
	t_path	*rt;

	rt = (t_path*)ft_memalloc(sizeof(t_path));
	if (rt == 0)
		exit (1);
	rt->str = ft_strdup(str);
	rt->size = ft_strlen(str);
	return (rt);
}

void	push_path(t_app *app, char *str)
{
	if (!app->nb_path)
	{
		app->first_path = new_path(str);
		app->last_path = app->first_path;
	}
	else
	{
		app->last_path->next = new_path(str);
		app->last_path->next->previous = app->last_path;
		app->last_path = app->last_path->next;
	}
	app->nb_path++;
}

void	pop_path(t_app *app)
{
	t_path	*tmp;

	tmp = app->last_path;
	if (!app->nb_path)
		return ;
	else if (app->nb_path != 1)
	{
		app->last_path = app->last_path->previous;
		app->last_path->next = 0;
	}
	free(tmp->str);
	free(tmp);
	app->nb_path--;
}

void	print_path(t_app *app)
{
	t_path	*tmp;
	unsigned int i;

	tmp = app->first_path;
	i = app->nb_path;
	while (i && tmp)
	{
		ft_putstr(tmp->str);
		ft_putstr("/");
		tmp = tmp->next;
		i--;
	}
	ft_putstr("\n");
}

char	*path_str(t_app *app)
{

}
