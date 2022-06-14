# Makefile

CPPFLAGS = -MMD
CC = gcc -lreadline -g
CFLAGS = -Wall -Wextra -c -std=c99
LDFLAGS =

SRC = ${wildcard src/*.c}
HDR = ${wildcard include/*.h}
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
EXEC = 2Ash

all: ${SRC} ${OBJ} ${EXEC}

${EXEC}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

%.o: %.c ${HDR}
	${CC} ${CFLAGS} $< -o $@

.PHONY: clean

debug: all
debug: CC += -fsanitize=address -DDEBUG

clean:
	${RM} ${EXEC}
	${RM} ${OBJ}
	${RM} ${DEP}

-include ${DEP}

# END
#
