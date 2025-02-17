##
## EPITECH PROJECT, 2025
## Untitled (Workspace)
## File description:
## Makefile
##

NAME	=	mydream

CC	=	gcc

RM	=	rm -f

SRCDIR	=	src/

SRCS	=	$(wildcard $(SRCDIR)*.c)

OBJDIR	=	obj/

OBJS	=	$(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)

CFLAGS	=	-I./Include -Wall -Wextra -g

LDFLAGS	=	-lSDL2 -lSDL2_image -lm -lSDL2_ttf -lSDL2_mixer

all:	$(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:	$(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

debug: CFLAGS += -g
debug: re

run: all
	./$(NAME)

.PHONY: all clean fclean re debug run
