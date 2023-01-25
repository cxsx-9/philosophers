NAME = philosophers

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
SRC = main.c util.c dinner.c init.c routine.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -I philosophers.h $(OBJ) -o $(NAME) 

clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY : all clean fclean re
