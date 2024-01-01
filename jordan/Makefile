Name = dParse
CC = cc
CFLAGS = -Wall
INCS = Parser.h Node.h union.h CharItr.h Guards.h Token.h Scanner.h

SRC = src/main.c src/Parser.c src/Node.c src/union.c src/CharItr.c src/Guards.c 

OBJ = $(SRC:.c=.o)

%.o:%.c
	$(CC) $(CFLAGS) -I INCS -c $< -o $@

all: $(Name)

$(Name): $(OBJ)
	$(CC)  $(OBJ) -o $(Name)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(Name)

re: fclean all

.PHONY: clean