CC=gcc
CFLAGS=-O3 -Wall
LIBS=-pthread
SRC=src

all: server.out client.out

server.o: $(SRC)/server.c
	$(CC) $(CFLAGS) -c $(SRC)/server.c
string.o: $(SRC)/string.c
	$(CC) $(CFLAGS) -c $(SRC)/string.c
client.o: $(SRC)/client.c
	$(CC) $(CFLAGS) -c $(SRC)/client.c
game.o: $(SRC)/game.c
	$(CC) $(CFLAGS) -c $(SRC)/game.c
server.out: server.o
	$(CC) $(CFLAGS) $(LIBS) -o server.out server.o game.o
client.out: client.o string.o
	$(CC) $(CFLAGS) $(LIBS) -o client.out client.o string.o


.PHONY: clean

clean: 
	rm -f *.o *.out