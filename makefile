CC = gcc
CFLAGS = -march=native -Wall -Wshadow -g
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
TARGETS = malloc.so demo

all: $(TARGETS)

malloc.so: malloc.o
	$(CC) $(CFLAGS) -fPIC -o $@ $^

demo: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGETS)
