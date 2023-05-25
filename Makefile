OBJS = src/main.c src/tools/binarypartitioner.c src/tools/fileinit.c src/tools/filevalidcheck.c src/gui/mainmenu.c src/gui/argselect.c src/gui/pwadselect.c src/gui/paraselect.c src/gui/infoscreen.c
CFLAG = -Wall -Werror -Wpedantic -g
CC = gcc
INCLUDE =
LIBS = -lncurses

# This is used for formatting.
FM = astyle
FFLAG = -s2 -n -A3


sldl:${OBJ}
	${CC} ${CFLAG} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

format:${OBJ}
	${FM} ${OBJS} ${FFLAG} 

clean:
	rm sldl
