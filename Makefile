CC=gcc
CFLAGS = -Wall -Werror -pedantic -std=gnu99

template: template.c

clean:
	rm -f template
