NAME = main
CC = cc
CFLAGS = -Wall -Werror -Wextra 
INCS_DIR = includes/
INCS = main.h
LIBFT= libft.a

SRC = main.c
OBJ = $(SRC:.c=.o)

%.o: %.c 
	$(CC) $(CFLAGS) -I $(INCS_DIR) -c $< -o $@ 

all: $(NAME) $(LIBFT)

$(NAME): $(OBJ)
	make -C lib
	$(CC) $(CFLAGS) lib/$(LIBFT) $(OBJ) -o $(NAME) -lreadline

clean:
	make -C lib clean
	rm -f $(OBJ)

fclean: clean
	make -C lib fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

