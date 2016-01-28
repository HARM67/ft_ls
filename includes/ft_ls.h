#ifndef FT_LS_H
# define FT_LS_H
# include <sys/ioctl.h>
# include <dirent.h>
# include <stdlib.h>
# include "ft_printf.h"

typedef struct		s_path
{
	char			*str;
	int				len;
	struct s_path	*next;
	struct s_path	*previous;
}					t_path;

typedef struct		s_elem
{
	char			name[256];
	unsigned int	name_len;
	unsigned int	size;
	unsigned int	type;
	struct s_elem	*next;
	struct s_elem	*previous;
	struct s_elem	*next_sort;
	struct s_elem	*Previous_sort;
}					t_elem;

typedef struct		s_lst_elem
{
	t_elem			*first;
	t_elem			*last;
	unsigned int	nb_elem;
}					t_lst_elem;

typedef struct		s_app
{
	int				ac;
	char			**av;
	t_path			*first_path;
	t_path			*last_path;
	unsigned int	nb_path;
	unsigned int	path_len;
	int				row;
	int				col;
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

/*
** elem.c
*/
t_elem				*new_elem(struct dirent *d);
void				push_elem(t_lst_elem *lst, struct dirent *d);

/*
** recursive.c
*/
void				parcour(t_app *app);
#endif
