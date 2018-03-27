all: clean main.o add.o sub.o mult.o div.o
	gcc -g -Wall -o calc main.o add.o sub.o mult.o div.o

main.o:
	gcc -g -Wall -c -o main.o main.c

add.o:
	nasm -g -f elf64 -w+all -o add.o add.s

sub.o:
	nasm -g -f elf64 -w+all -o sub.o sub.s

mult.o:
	nasm -g -f elf64 -w+all -o mult.o mult.s

div.o:
	nasm -g -f elf64 -w+all -o div.o div.s

.PHONY: clean
clean:
	rm -f *.o calc