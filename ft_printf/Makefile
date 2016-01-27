NAME = libftprintf.a
FLAG = -Wall -Werror -Wextra
COMPILER = gcc
SRCS_PATH = ./srcs/
SRC = ft_printf.c itoa_4.c itoa_2.c itoa_1.c itoa_8.c \
		uitoa_base_1.c uitoa_base_2.c uitoa_base_4.c uitoa_base_8.c \
		insert_flag.c argtoa.c read_flag.c print_arg.c \
		ft_putchar.c ft_putstr.c ft_bzero.c ft_memset.c \
		ft_memcpy.c ft_putnbr.c ft_memccpy.c ft_memmove.c \
		ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c \
		ft_strcat.c ft_strncat.c ft_strlcat.c ft_strstr.c \
		ft_strcmp.c ft_strncmp.c ft_isupper.c ft_islower.c \
		ft_isalpha.c ft_atoi.c ft_isdigit.c ft_isalnum.c \
		ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
		ft_memchr.c ft_memcmp.c ft_strchr.c ft_strrchr.c \
		ft_strnstr.c ft_memalloc.c ft_memdel.c ft_strnew.c \
		ft_strdel.c ft_strclr.c	ft_striter.c ft_striteri.c \
		ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
		ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c\
		ft_strclen.c ft_strnext.c ft_strcount.c ft_putchar_fd.c  \
		ft_putendl.c ft_putstr_fd.c ft_putnbr_fd.c ft_itoa.c\
		ft_putendl_fd.c ft_lstnew.c ft_lstdelone.c \
		ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c \
		unicode.c ft_strncon.c ftoa.c flag_tool.c stoa.c make_str.c \
		printf_loop.c n_base.c color.c
INCLUDES  = ./includes
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: $(SRCS_PATH)%.c
	$(COMPILER) -c $(FLAG) $< -I$(INCLUDES)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re: fclean all
