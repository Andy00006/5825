CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
OBJ = main.o fonctions.o

all: prog

prog: $(OBJ)
	$(CC) $(CFLAGS) -o prog $(OBJ)

main.o: main.c header.h
	$(CC) $(CFLAGS) -c main.c

fonctions.o: fonctions.c header.h
	$(CC) $(CFLAGS) -c fonctions.c

clean:
	rm -f *.o prog
