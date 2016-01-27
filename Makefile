NAME=ft_ls
SRC_PATH=./SRCS/
INCLUDES=./includes

all: 
	gcc -I$(INCLUDES) $(SRC_PATH)main.c -o $(NAME)
