CC=gcc
CFLAGS=-Wall -Wextra -std=gnu99 

all: main

main: main.o -lm

clean:
	rm -rf main *.o
