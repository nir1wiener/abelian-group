all: main
	 ./MyGroupMain


main:  Complex.o GenGroup.o  GenGroup MyGroupMain.o 
	gcc -g  Complex.o MyGroupMain.o -L. -lgenGroup  -o MyGroupMain 
	


MyGroupMain.o: MyGroupMain.c GenGroup
	gcc -g -std=c99 -Wall -Wextra -Wvla  -c MyGroupMain.c 

GenGroup: GenGroup.o 
	ar rcs libgenGroup.a GenGroup.o 


Complex.o: Complex.c Complex.h
	gcc -g -std=c99 -Wall -Wextra -Wvla -c Complex.c

GenGroup.o: GenGroup.c GenGroup.h
	gcc  -g -std=c99 -Wall -Wextra -Wvla -c GenGroup.c

clean: 
	rm -f Complex.o main  GenGroup.o MyGroupMain.o GenGroup libgenGroup.a



