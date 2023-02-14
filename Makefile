# Makefile for Lab-04

CC = gcc
CFLAGS = -Wall -g
OBJS = Hw2.o
SEARCH = FileTraverse.o
EXECS = search
TARGETFOLDER = project1

build : search
	./$^ -S $(TARGETFOLDER)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(EXECS): $(OBJS) $(SEARCH)
	$(CC) $(CFLAGS) -o $@ $^
	rm $^

debug :	Hw2
	gdb ./Hw2 -tui

test: search
	./$^
	./$^ -S $(TARGETFOLDER)
	./$^ -f txt 1 $(TARGETFOLDER)
	./$^ -s 1024 $(TARGETFOLDER)
	./$^ -t d $(TARGETFOLDER)
	./$^ -S -s 1024 -f .c 1 -t f $(TARGETFOLDER)

clean : 
	rm *.o