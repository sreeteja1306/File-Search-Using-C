# Makefile for Lab-04

CC = gcc
CFLAGS = -Wall -g
OBJS = Hw2.o
SEARCH = FileTraverse.o
EXECS = Hw2

build : Hw2
	./Hw2 -f tt 6 -s 1024 -S

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

Hw2 : $(OBJS) $(SEARCH)
	$(CC) $(CFLAGS) -o $@ $^

debug :	Hw2
	gdb ./Hw2 -tui

clean : 
	rm *.o $(EXECS)