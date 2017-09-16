CC=clang
CFLAGS=-I. -Wall -Werror -std=c99
LDFLAGS=-lncurses
DEPS=pong.h

%.o: %.c $(DEPS) 
	$(CC) -c -o $@ $< $(CFLAGS)

pong: main.o pong.o
	gcc -o pong main.o pong.o -I. $(LDFLAGS)

