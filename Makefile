OBJS = src/main.c
CFLAG = -Wall -Werror -Wpedantic
CC = gcc
INCLUDE =
LIBS =

# This is used for formatting.
FM = astyle
FFLAG = -s2 -n


sldl:${OBJ}
	${CC} ${CFLAG} ${INCLUDES} -o $@ ${OBJS} ${LIBS} -g

format:${OBJ}
	${FM} ${OBJS} ${FFLAG} 

clean:
	rm sldl
