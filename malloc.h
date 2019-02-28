#ifndef MALLOC_H
#define MALLOC_H

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nelem, size_t elsize);
void free(void *ptr);
struct block_meta *request_space(struct block_meta *last, size_t size);
struct block_meta *find_free_block(struct block_meta **last, size_t size);
struct block_meta *get_block_ptr(void *ptr);

void print_block(struct block_meta *ptr, int first, int last);
void show_heap();

#define META_SIZE sizeof(struct block_meta)
#define min(X, Y) ((X) < (Y) ? (X) : (Y))
#define max(X, Y) ((X) > (Y) ? (X) : (Y))

struct block_meta{
  size_t size;
  struct block_meta *next;
  int free;
  int magic; // debugging only TODO: remove this
};

#endif
