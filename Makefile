CC := gcc
CFLAGS := -Wall
DIR := src/

all: c_ep1 f_ep1 f2c_ep1

c_ep1: $(DIR)c_ep1.c
	$(CC) $^ -o c_ep1

f_ep1: $(DIR)f_ep1.f
	gfortran $^ -o f_ep1

f2c_ep1: $(DIR)f_ep1.c
	$(CC) -L/usr/lib -lf2c $^ -o f2c_ep1

genmat: $(DIR)genmat.c

clean:
	rm c_ep1 f_ep1 f2c_ep1
