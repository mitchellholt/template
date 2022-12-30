CC=gcc
CFLAGS = -Wall -Werror -pedantic -std=gnu99

template: template.o search.o priorityQueue.o

template.o: template.c search.h

search.o: search.c search.h

priorityQueue.o: priorityQueue.c priorityQueue.h

clean:
	rm -f template *.o
