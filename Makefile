##
## EPITECH PROJECT, 2025
## MyDream
## File description:
## Makefile
##

NAME	=	mydream

CC	=	gcc

RM	=	rm -f

SRCS	=	src/enemy.c \
		src/enemy_render.c \
		src/enemy_update.c \
		src/engine.c \
		src/engine_ray.c \
		src/game.c \
		src/main.c \
		src/map.c \
		src/map_editor.c \
		src/menu.c \
		src/player.c \
		src/sound.c \
		src/text.c \
		src/weapon.c

CFLAGS	=	-I./Include -Wall -Wextra

LDFLAGS	=	-lSDL2 -lSDL2_image -lm -lSDL2_ttf -lSDL2_mixer

all:	$(NAME)

$(NAME):
	$(CC) $(SRCS) -o $(NAME) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(NAME)

fclean:	clean

re:	fclean all

debug: CFLAGS += -g
debug: re

run: all
	./$(NAME)

.PHONY: all clean fclean re debug run