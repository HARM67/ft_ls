#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <stdlib.h>
# include "ft_printf.h"

typedef struct		s_path
{
	char			*str;
	int				size;
	struct s_path	*next;
	struct s_path	*previous;
}					t_path;

typedef struct		s_app
{
	int				ac;
	char			**av;
	t_path			*first_path;
	t_path			*last_path;
	unsigned int	nb_path;
}					t_app;

/*
** app.c
*/
void				init_app(t_app *app);
void				run_app(t_app *app);

/*
** path.c
*/
t_path				*new_path(char *str);
void				push_path(t_app *app, char *str);
void				pop_path(t_app *app);
void				print_path(t_app *app);
char				*path_str(t_app *app);
#endif
