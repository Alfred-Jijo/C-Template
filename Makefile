NAME = template
VERSION = 0.0.0
PREFIX ?= $(HOME)/.local

CC ?= cc
CFLAGS = -Wall -Wextra -Werror -pedantic -Wno-unused-parameter

SRC = lib/ds.c src/main.c
OBJ = ds.o main.o
INCLUDE = -Iinclude

all: $(NAME)

<<<<<<< HEAD
run: program
	./${OUT}
=======
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(INCLUDE)

ds.o:
	$(CC) -c lib/ds.c -o $@ $(CFLAGS) $(INCLUDE)

main.o:
	$(CC) -c src/main.c -o $@ $(CFLAGS) $(INCLUDE)

run: $(NAME)
	./$(NAME)
>>>>>>> d43e59d4bcc553be24b9824b6d348cdd95ac28c8

clean:
	rm $(OBJ)
	rm $(NAME)
