CC=gcc
SRC=brainfuck.c
TARGET=brainfuck
CFLAGS=-Wall
all:
	${CC} ${SRC} -o ${TARGET} ${CFLAGS}

clean:
	rm -rf *.o ${TARGET}

unittest:
	cd test; \
	./test.sh;
