CC := gcc
CFLAGS := -std=c99 -Wall -lm

all: ep1 genmat

ep1: ep1.c

genmat: genmat.c

clean:
	rm *~
