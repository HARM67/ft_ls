NAME=ft_ls
INCLUDES=./includes
INCLUDES_FT_PRINTF=./ft_printf/includes
CC = gcc
LIB=./ft_printf/
SRC_PATH=./srcs/
FLAG=-Wall -Wextra -Werror

SRCS= app.c path.c elem.c elem2.c print_elem.c lst_elem.c recursive.c \
		read_stat.c read_arg.c check_arg.c mode.c comparison.c put_error.c \
		comparison2.c main.c

OBJ=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIB)libftprintf.a $(OBJ) $(INCLUDES_FT_PRINTF)/ft_printf.h \
	$(INCLUDES)/ft_ls.h
	$(CC) $(FLAG) -o $(NAME) -I$(INCLUDES_FT_PRINTF) -I$(INCLUDES) $(OBJ) -L$(LIB) -lftprintf

%.o: $(SRC_PATH)%.c $(INCLUDES)/ft_ls.h
	$(CC) -c $(FLAG) $< -I$(INCLUDES_FT_PRINTF) -I$(INCLUDES)

$(LIB)libftprintf.a:
	make -C $(LIB)
	make clean -C $(LIB)

clean:
	make clean -C $(LIB)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIB)
	rm -f $(NAME)

re: fclean $(NAME)
