program: main.o function.o ./hashing/hash_function.o
	gcc -o program main.o function.o ./hashing/hash_function.o -I.

main.o: main.c
	gcc -c main.c

function.o: function.c
	gcc -c function.c

