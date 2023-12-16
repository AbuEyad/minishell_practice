NAME = main
CC = cc
CFLAGS = #-Wall -Werror -Wextra 
INCS_DIR = includes/
INCS = main.h
LIBFT= libft.a

SRC = main.c
OBJ = $(SRC:.c=.o)

%.o: %.c 
	$(CC) $(CFLAGS) -I $(INCS_DIR) -c $< -o $@ 

all: $(NAME)

$(NAME): $(OBJ)
	make -C lib
	$(CC) $(CFLAGS) $(OBJ) lib/$(LIBFT) -lreadline -o $(NAME) 

clean:
	make -C lib clean
	rm -f $(OBJ)

fclean: clean
	make -C lib fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

