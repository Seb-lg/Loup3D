SRC	=	main.c				\
		src/graphics.c		\
		src/gaming.c		\
		src/inputs.c		\
		src/struct/color.c	\
		src/struct/player.c	\
		src/struct/vector.c	\
		src/struct/cast.c	\

OBJ = $(SRC:.c=.o)

CFLAGS += -g -Werror -Wextra -I./include

# CFLAGS += -o3

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