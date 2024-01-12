Name = dParse
CC = cc
CFLAGS = -Wall
INCS = include/Parser.h include/Node.h \
		include/union.h include/CharItr.h \
		include/Guards.h include/Token.h \
		include/Scanner.h include/Vec.h \
		include/StrVec.h include/Str.h include/Exec.h

SRC = src/main.c src/Parser.c src/Node.c \
	src/union.c src/CharItr.c src/Guards.c \
	src/Vec.c src/StrVec.c src/Scanner.c src/Str.c src/Exec.c

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