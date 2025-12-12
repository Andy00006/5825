CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = main.o fonctions_avl.o fonctions_fuites.o

all: mon_programme

mon_programme: $(OBJ)
	$(CC) $(CFLAGS) -o mon_programme $(OBJ)

main.o: main.c en_tete.h
	$(CC) $(CFLAGS) -c main.c

fonctions_avl.o: fonctions_avl.c en_tete.h
	$(CC) $(CFLAGS) -c fonctions_avl.c

fonctions_fuites.o: fonctions_fuites.c en_tete.h
	$(CC) $(CFLAGS) -c fonctions_fuites.c

clean:
	rm -f *.o mon_programme
