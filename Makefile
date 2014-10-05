CC := gcc
CFLAGS := -Wall

all: ep1 genmat

ep1: ep1.c

genmat: genmat.c

clean:
	rm *~
