SRC	=	main.c				\
		src/graphics.c		\
		src/gaming.c		\
		src/inputs.c		\
		src/struct/color.c	\
		src/struct/player.c	\

OBJ = $(SRC:.c=.o)

CFLAGS += -g -Werror -Wextra -I./include

CFLAGS += -lglfw -lGL -lm

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