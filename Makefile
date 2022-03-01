SRC	=	main.c				\
		src/graphics.c		\
		src/inputs.c		\
		src/game_engine.c	\
		src/struct/cast.c	\
		src/struct/color.c	\
		src/struct/player.c	\
		src/struct/vector.c	\

OBJ = $(SRC:.c=.o)

CFLAGS += -g -Werror -Wextra -I./include

CFLAGS += -pg

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