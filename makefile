CC = gcc
CFLAGS = -march=native -Wall -Wshadow
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

all: malloc malloc.so

malloc.so: $(SRC)
	$(CC) $(CFLAGS) -fPIC -o $@ $^

malloc: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) malloc.so malloc
