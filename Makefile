NAME=ft_ls
SRC_PATH=./SRCS/
INCLUDES=-I./includes -I./ft_printf/includes
LIB=-L./ft_printf/

all: 
	gcc $(INCLUDES) -o $(NAME) $(LIB) -lftprintf \
		$(SRC_PATH)app.c \
		$(SRC_PATH)path.c \
		$(SRC_PATH)main.c

