CC = gcc
CFLAGS = -march=native -Wall -Wshadow -g -O0
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
TARGETS = malloc.so demo

all: $(TARGETS)

malloc.so: malloc.c
	$(CC) $(CFLAGS) -c -fPIC -o $@ $^

demo: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGETS)
