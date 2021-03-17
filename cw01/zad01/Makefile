CC = gcc
CC_FLAGS = -Wall -std=c11

static:
	$(CC) $(CC_FLAGS) -c merge.c -o libmerge.o
	ar rcs libmerge.a libmerge.o

shared:
	$(CC) $(CC_FLAGS) -fPIC -shared merge.c -o libmerge.so

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so