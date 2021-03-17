CC = gcc
FLAGS = -Wall -std=c11
RAPORT3A = raport3a.txt
RAPORT3B = raport3b.txt

static:
	$(CC) $(FLAGS) -c merge.c -o libmerge.o
	ar rcs libmerge.a libmerge.o

shared:
	$(CC) $(FLAGS) -fPIC -shared merge.c -o libmerge.so

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.so

staticMain: clean static
	$(CC) $(FLAGS) main.c -static -L. -lmerge -o output

sharedMain: clean shared
	$(CC) $(FLAGS) main.c -lmerge -L. -Wl,-rpath=. -o output

dynamicMain:
	$(CC) $(FLAGS) mainDynamic.c -ldl -o output

runTestA:
	./output test >> $(RAPORT3A)

runTestB:
	./output test >> $(RAPORT3B)

raportA:
	make staticMain
	@echo "====================================" >> $(RAPORT3A)
	@echo "------------STATIC TESTS------------" >> $(RAPORT3A)
	@echo "====================================" >> $(RAPORT3A)
	make runTestA

	make sharedMain
	@echo "====================================" >> $(RAPORT3A)
	@echo "------------SHARED TESTS------------" >> $(RAPORT3A)
	@echo "====================================" >> $(RAPORT3A)
	make runTestA

	make dynamicMain
	@echo "====================================" >> $(RAPORT3A)
	@echo "------------DYNAMIC TESTS------------" >> $(RAPORT3A)
	@echo "====================================" >> $(RAPORT3A)
	make runTestA

raportB:
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------(-O0 TESTS))------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)

	make clean
	make static
	$(CC) -O0 -Wall -std=c11 main.c -static -L. -lmerge -o output
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------STATIC TESTS------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)
	make runTestB

	make clean
	make shared
	$(CC) -O0 -Wall -std=c11 main.c -lmerge -L. -Wl,-rpath=. -o output
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------SHARED TESTS------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)
	make runTestB

	make clean
	make shared
	$(CC) -O0 -Wall -std=c11 mainDynamic.c -ldl -o output
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------DYNAMIC TESTS------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)
	make runTestB

	@echo "====================================" >> $(RAPORT3B)
	@echo "------------(-O2 TESTS))------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)

	make clean
	make static
	$(CC) -O2 -Wall -std=c11 main.c -static -L. -lmerge -o output
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------STATIC TESTS------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)
	make runTestB

	make clean
	make shared
	$(CC) -O2 -Wall -std=c11 main.c -lmerge -L. -Wl,-rpath=. -o output
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------SHARED TESTS------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)
	make runTestB

	make clean
	make shared
	$(CC) -O2 -Wall -std=c11 mainDynamic.c -ldl -o output
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------DYNAMIC TESTS------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)
	make runTestB

	@echo "====================================" >> $(RAPORT3B)
	@echo "------------(-O3 TESTS))------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)

	make clean
	make static
	$(CC) -O3 -Wall -std=c11 main.c -static -L. -lmerge -o output
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------STATIC TESTS------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)
	make runTestB

	make clean
	make shared
	$(CC) -O3 -Wall -std=c11 main.c -lmerge -L. -Wl,-rpath=. -o output
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------SHARED TESTS------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)
	make runTestB

	make clean
	make shared
	$(CC) -O3 -Wall -std=c11 mainDynamic.c -ldl -o output
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------DYNAMIC TESTS------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)
	make runTestB

	@echo "====================================" >> $(RAPORT3B)
	@echo "------------(-Ofast TESTS))------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)

	make clean
	make static
	$(CC) -Ofast -Wall -std=c11 main.c -static -L. -lmerge -o output
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------STATIC TESTS------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)
	make runTestB

	make clean
	make shared
	$(CC) -Ofast -Wall -std=c11 main.c -lmerge -L. -Wl,-rpath=. -o output
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------SHARED TESTS------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)
	make runTestB

	make clean
	make shared
	$(CC) -Ofast -Wall -std=c11 mainDynamic.c -ldl -o output
	@echo "====================================" >> $(RAPORT3B)
	@echo "------------DYNAMIC TESTS------------" >> $(RAPORT3B)
	@echo "====================================" >> $(RAPORT3B)
	make runTestB