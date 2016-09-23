# makefile -mp3_explorer-

CFLAGS = -Wall -pedantic -ansi -c -O3
CC = gcc

all: mp3_explorer

mp3_explorer: genres.o csv.o mp3.o vector.o main.o utilities.o globals.o english.o html.o xml.o
	$(CC) -o mp3_explorer genres.o csv.o mp3.o vector.o main.o utilities.o globals.o english.o html.o xml.o

genres.o: genres.c types.h
	$(CC) $(CFLAGS) genres.c -o genres.o

csv.o: csv.c csv.h
	$(CC) $(CFLAGS) csv.c -o csv.o

mp3.o: mp3.c mp3.h
	$(CC) $(CFLAGS) mp3.c -o mp3.o

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) vector.c -o vector.o

main.o: main.c main.h
	$(CC) $(CFLAGS) main.c -o main.o

utilities.o: utilities.c utilities.h
	$(CC) $(CFLAGS) utilities.c -o utilities.o

globals.o: globals.c types.h vector.h mp3.h csv.h html.h xml.h
	$(CC) $(CFLAGS) globals.c -o globals.o

english.o: english.c
	$(CC) $(CFLAGS) english.c -o english.o

html.o: html.c html.h
	$(CC) $(CFLAGS) html.c -o html.o

xml.o: xml.c xml.h
	$(CC) $(CFLAGS) xml.c -o xml.o

csv.h: lang.h types.h vector.h mp3.h

mp3.h: genres.h types.h utilities.h

main.h: vector.h mp3.h types.h lang.h utilities.h globals.h setup.h

utilities.h: types.h

vector.h: types.h

lang.h: types.h

html.h: mp3.h vector.h types.h

xml.h: mp3.h vector.h types.h

clean:
	rm *.o
