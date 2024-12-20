##
## KORO PROJECT, 2024
## MyDream
## File description:
## Makefile
##

NAME = mydream

SRC = src/main.c \
      src/ray.c\
	  src/window.c\
	  src/movement.c\
	  src/debug.c\

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Imodule
LDFLAGS = -lSDL2 -lm

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re