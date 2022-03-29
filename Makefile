# Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c -std=c99 -g
LDFLAGS = -g

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
debug: CC += -fsanitize=address -DDEBUG -g

clean:
	${RM} ${EXEC}
	${RM} ${OBJ}
	${RM} ${DEP}

-include ${DEP}

# END
