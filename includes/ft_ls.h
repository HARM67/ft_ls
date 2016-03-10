#ifndef FT_LS_H
# define FT_LS_H
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
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
	char			*path;
	unsigned int	name_len;
	unsigned int	user_len;
	unsigned int	grp_len;
	unsigned int	size;
	unsigned int	type;
	struct dirent	*dirent;
	struct s_elem	*next;
	struct s_elem	*previous;
	struct stat		stat;
	char			*user_name;
	char			*groupe_name;
	struct passwd	*passwd;
}					t_elem;

typedef struct		s_lst_elem
{
	t_elem			*first;
	t_elem			*last;
	unsigned int	nb_elem;
	unsigned int	max_name_len;
	unsigned int	max_file_name;
	unsigned int	max_grp_len;
	unsigned int	max_size;
	unsigned int	max_nlink;
	unsigned int	total;
	unsigned int	size;
}					t_lst_elem;

typedef struct		s_p_arg
{
	char			*path;
	struct s_p_arg	*next;
	struct s_p_arg	*previous;
}					t_p_arg;

typedef struct		s_app
{
	int				(*compare)(struct s_app *, t_elem*, t_elem*);
	void			(*print)(struct s_app *, t_lst_elem*);
	int				ac;
	char			**av;
	t_p_arg			*first_p_arg;
	t_p_arg			*last_p_arg;
	t_path			*first_path;
	t_path			*last_path;
	unsigned int	nb_p_arg;
	unsigned int	nb_path;
	unsigned int	path_len;
	int				row;
	int				col;
	unsigned char	show_hidden;
	unsigned char	recursive;
	unsigned char	recursive_depth;
	unsigned char	color;
	unsigned char	list;
	unsigned char	read_mode;
	unsigned char	temoin_recursive;
	char			reverse_sort;
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
char				*path_str(t_app *app, char option);

/*
** elem.c
*/
void				insert_elm(t_app *app, t_lst_elem *lst, struct dirent *d);
t_elem				*new_elem(struct dirent *d);
void				push_elem(t_app * app, t_lst_elem *lst, struct dirent *d);
void				clean_lst(t_lst_elem *lst);
void				print_elem_list(t_app *app, t_elem *elm, t_lst_elem *lst);

/*
** lst_elem.c
*/
unsigned int		nbr_len(unsigned int nbr);
void				print_lst(t_app *app, t_lst_elem *lst);
void				print_lst_list(t_app *app, t_lst_elem *lst);

/*
** recursive.c
*/
void				parcour(t_app *app);

/*
** read_stat.c
*/
void				read_stat(t_elem *elm);

/*
** mode.c
*/
void				write_mode(mode_t mode);

/*
** comparison.c
*/
int					compare_size(t_app *app, t_elem *elm1, t_elem *elm2);
int					compare_ascii(t_app *app, t_elem *elm1, t_elem *elm2);
int					compare_modif(t_app *app, t_elem * elm1, t_elem *elm2);

/*
** read_arg.c
*/
t_p_arg				*new_p_arg(t_app *app, char *path);
void				insert_p_arg(t_app *app, char *path);
void				read_arg(t_app *app);
#endif
