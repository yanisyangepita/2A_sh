# Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -Werror -c -std=c99 -g
LDFLAGS = -g

SRC = ${wildcard src/*.c}
HDR = ${wildcard include/*.c}
OBJ = ${SRC:.c=.o}
EXEC = lex

all: ${SRC} ${OBJ} ${EXEC}

${EXEC}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

%.o: %.c ${HDR}
	${CC} ${CFLAGS} $< -o $@

.PHONY: clean

clean:
	${RM} ${EXEC}
	${RM} ${OBJ}

# END
