out : main.o TMemoria.o TMemoria.h
	gcc TMemoria.o main.o -o out

main.o : main.c TMemoria.h
	gcc -c main.c -o main.o -Wall

TMemoria.o : TMemoria.c TMemoria.h
	gcc -c TMemoria.c -o TMemoria.o -Wall

clean :
	rm TMemoria.o main.o out
