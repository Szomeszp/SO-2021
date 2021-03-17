CC = gcc
FLAGS = -Wall -std=c11

static:
	$(CC) $(FLAGS) -c merge.c -o libmerge.o
	ar rcs libmerge.a libmerge.o

shared:
	$(CC) $(FLAGS) -fPIC -shared merge.c -o libmerge.so

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so