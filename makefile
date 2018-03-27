all: clean main.o #add.o
	gcc -g -Wall -o run main.o #add.o

main.o:
	gcc -g -Wall -c -o main.o main.c
	
#add.o:
#	nasm -g -f elf64 -w+all -o add.o add.s

.PHONY: clean
clean:
	rm -f *.o run