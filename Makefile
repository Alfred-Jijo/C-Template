NAME = template
VERSION = 0.0.0
PREFIX ?= $(HOME)/.local

CC ?= cc
CFLAGS = -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -std=c99

SRC = lib/ds.c src/main.c
OBJ = $(SRC:%.c=%.o)
INCLUDE = -Iinclude

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(INCLUDE)

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

run: $(NAME)
	./$(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

.PHONY: all clean
