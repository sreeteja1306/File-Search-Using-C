# Makefile for Lab-04

CC = gcc
CFLAGS = -Wall -g
OBJS = Hw2.o
EXECS = Hw2

build : Hw2
	./Hw2 -f -s -S -f -s -S

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

lab04 : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

debug :	Hw2
	gdb ./Hw2 -tui

clean : 
	rm *.o $(EXECS)