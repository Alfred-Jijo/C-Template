PREFIX = ${HOME}/.local
CC ?= cc
CFLAGS += -Wall -Wextra
SOURCE += lib/ds.c src/*.c
INCLUDE += include
OUT=out

all: program

program:
	${CC} ${CFLAGS} -I./${INCLUDE} ${SOURCE} -o ${OUT}

run: program
	./${OUT}

clean:
	rm ${OUT}
