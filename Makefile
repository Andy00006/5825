CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o animal.o

refuge: $(OBJ)
	$(CC) $(CFLAGS) -o refuge $(OBJ)

main.o: main.c animal.h
	$(CC) $(CFLAGS) -c main.c

animal.o: animal.c animal.h
	$(CC) $(CFLAGS) -c animal.c

clean:
	rm -f *.o refuge
