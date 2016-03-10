NAME=ft_ls
SRC_PATH=./srcs/
INCLUDES=-I./includes -I./ft_printf/includes
LIB=-L./ft_printf/

all: 
	gcc $(INCLUDES) -o $(NAME) $(LIB) -lftprintf -g \
		$(SRC_PATH)app.c \
		$(SRC_PATH)path.c \
		$(SRC_PATH)elem.c \
		$(SRC_PATH)lst_elem.c \
		$(SRC_PATH)recursive.c \
		$(SRC_PATH)read_stat.c \
		$(SRC_PATH)read_arg.c \
		$(SRC_PATH)mode.c \
		$(SRC_PATH)comparison.c \
		$(SRC_PATH)main.c

