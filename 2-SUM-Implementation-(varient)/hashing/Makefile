hash: main.o hash_function.o
	gcc -o hash main.o hash_function.o -I.

hash_function.o: hash_function.c
	gcc -c hash_function.c

main.o: main.c
	gcc -c main.c
