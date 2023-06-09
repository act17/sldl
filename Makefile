OBJS = src/main.c src/tools.c src/gui/mainmenu.c src/gui/argselect.c src/gui/pwadselect.c src/gui/paraselect.c src/gui/infoscreen.c
CFLAG = -Wall -Wpedantic -Werror -O2
DFLAG = -Wall -Wpedantic -g
CC = gcc
INCLUDE =
LIBS = -lncurses

# This is used for formatting.
FM = astyle
FFLAG = -s2 -n -A3 -U

sldl:${OBJ}
	${CC} ${CFLAG} ${INCLUDES} -o $@ ${OBJS} ${LIBS}

debug:${OBJ}
	${CC} ${DFLAG} ${INCLUDES} -o sldl-debug ${OBJS} ${LIBS}

format:${OBJ}
	${FM} ${OBJS} ${FFLAG} 

clean:
	rm sldl

dclean:
	rm sldl-debug
