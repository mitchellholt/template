CC=gcc
CFLAGS=-Wall -Werror -pedantic -std=gnu99
PRG=template

$(PRG): main.c template.o
	$(CC) $(CFLAGS) $< template.o -o $(PRG)

template.o: template.c template.h

debug: CFLAGS += -g
debug: $(PRG)

clean:
	rm -f *.o $(PRG)
