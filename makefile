all: clean main.o add.o sub.o divBy2.o
	gcc -g -Wall -o calc main.o add.o sub.o divBy2.o
	rm -f *.o

main.o:
	gcc -g -Wall -c -o main.o main.c

add.o:
	nasm -g -f elf64 -w+all -o add.o add.s

sub.o:
	nasm -g -f elf64 -w+all -o sub.o sub.s

divBy2.o:
	nasm -g -f elf64 -w+all -o divBy2.o divBy2.s

.PHONY: clean
clean:
	rm -f *.o calc