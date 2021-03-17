CC = gcc
CC_FLAGS = -Wall -std=c11
RAPORT2 = raport2.txt

static:
	$(CC) $(CC_FLAGS) -c merge.c -o libmerge.o
	ar rcs libmerge.a libmerge.o

shared:
	$(CC) $(CC_FLAGS) -fPIC -shared merge.c -o libmerge.so

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so

staticMain: clean static
	$(CC) $(CC_FLAGS) main.c -static -L. -lmerge -o output

sharedMain: clean shared
	$(CC) $(CC_FLAGS) main.c -lmerge -L. -Wl,-rpath=. -o output

runTest:
	./output test >> $(RAPORT2)

raport:
	make staticMain
	@echo "====================================" >> $(RAPORT2)
	@echo "------------STATIC TESTS------------" >> $(RAPORT2)
	@echo "====================================" >> $(RAPORT2)
	make runTest
	make sharedMain
	@echo "====================================" >> $(RAPORT2)
	@echo "------------SHARED TESTS------------" >> $(RAPORT2)
	@echo "====================================" >> $(RAPORT2)
	make runTest