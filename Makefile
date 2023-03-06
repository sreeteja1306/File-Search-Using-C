# Makefile for Lab-04

CC = gcc
CFLAGS = -Wall -g
OBJS = Hw2.o
SEARCH = FileTraverse.o
EXECS = search
TARGETFOLDER = projects

build : search
	./$^ -s 1024 -e "ls -l" $(TARGETFOLDER)

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
	./$^ -f .c 3 $(TARGETFOLDER)
	./$^ -s 1024 $(TARGETFOLDER)
	./$^ -t d $(TARGETFOLDER)
	./$^ -t f $(TARGETFOLDER)
	./$^ -S -s 1024 -f .c 3 -t f $(TARGETFOLDER)
	./$^ -s 1024 -e "ls -l" $(TARGETFOLDER)
	./$^ -f docx 3 -E "tar cvf docx.tar" $(TARGETFOLDER)
	./$^ -s 1024 -f jpg 3 -e "wc -l" $(TARGETFOLDER)

clean : 
	rm *.o