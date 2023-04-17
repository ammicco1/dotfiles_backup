main: main.o manipulate_string.o
	gcc -o main main.o manipulate_string.o

main.o: main.c
	gcc -c main.c

manipulate_string.o: manipulate_string.c
	gcc -c manipulate_string.c