SRC	=	main.c				\
		src/graphics.c		\

OBJ = $(SRC:.c=.o)

CFLAGS += -g -Werror -Wextra -I./include

CFLAGS += -lglut -lGL

NAME = Loup3D

$(NAME): $(OBJ)
		gcc $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re