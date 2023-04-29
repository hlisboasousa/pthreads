CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm -lpthread

ex1: main.o trio.o spend_time.o
	$(CC) $(CFLAGS) -o ex1 main.o trio.o spend_time.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

trio.o: trio.c
	$(CC) $(CFLAGS) -c trio.c

spend_time.o: spend_time.c
	$(CC) $(CFLAGS) -c spend_time.c

run: 
	make && ./ex1

clean:
	rm -f *.o ex1