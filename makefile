CC = gcc
CFLAGS = -march=native -fPIC -Wall -Wshadow -g -O0
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
TARGETS = malloc.so demo

all: $(TARGETS)

malloc.so: malloc.o
	$(CC) $(CFLAGS) -shared -o $@ $^

demo: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGETS)
