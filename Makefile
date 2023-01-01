CC=gcc
CFLAGS = -Wall -Werror -pedantic -std=gnu99

template: priorityQueue.o file.o search.o template.o
	$(CC) $(CFLAGS) priorityQueue.o file.o search.o template.o -o $@

template.o: template.c search.h file.h

search.o: search.c search.h priorityQueue.h

priorityQueue.o: priorityQueue.c priorityQueue.h

file.o: file.c file.h

debug: CFLAGS += -g
debug: template

clean:
	rm -f template *.o
