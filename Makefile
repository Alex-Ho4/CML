CFLAGS= -Wall -g -O0


all:example1 example2 calloc_test realloc_test

example1: example1.c malloc.c
example2: example2.c malloc.c
calloc_test: calloc_test.c malloc.c
realloc_test: realloc_test.c malloc.c

clean:
	-rm -f example1 example2 calloc_test realloc_test
