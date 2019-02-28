#include "malloc.h"

void *global_base = NULL;

void *malloc(size_t size){
  struct block_meta *block; // TODO: align size?

  if (size <= 0) {
    return NULL;
  }

  if (!global_base) { // first call
    block = request_space(NULL, size);
    if (!block) {
      return NULL;
    }
    global_base = block;
  } else {
    struct block_meta *last = global_base;
    block = find_free_block(&last, size);
    if (!block) {
      return NULL;
    } else { // found free block
      // TODO: consider splitting free block here
      block->free = 0;
      block->magic = 0x77777777;
    }
  }
  return (block+1);
}

void *realloc(void *ptr, size_t size){
  if (!ptr) {
    return malloc(size); // NULL ptr, act just like malloc
  }

  struct block_meta *block_ptr = get_block_ptr(ptr);
  if (block_ptr->size >= size) {
    // we have enough space
    // could free space once split is implemented
    return ptr;
  }

  // real implementation here
  void *new_ptr;
  new_ptr = malloc(size);
  if (!new_ptr) {
    return NULL; // TODO: set errno on fail
  }
  memcpy(new_ptr, ptr, block_ptr->size);
  free(ptr);
  return new_ptr;
}

void *calloc(size_t nelem, size_t elsize){
  size_t size = nelem * elsize; // TODO: check for overflow
  void *ptr = malloc(size);
  memset(ptr, 0, size);
  return ptr;
}

void free(void *ptr){
  if (!ptr){
    return;
  }

  // TODO: consider merging blocks once splitting blocks is implemented
  struct block_meta* block_ptr = get_block_ptr(ptr);
  assert(block_ptr->free == 0);
  assert(block_ptr->magic == 0x77777777 || block_ptr->magic == 0x12345678);
  block_ptr->free = 1;
  block_ptr->magic = 0x55555555;
}

struct block_meta *find_free_block(struct block_meta **last, size_t size){
  struct block_meta *current = global_base;
  while (current && !(current->free && current->size >= size)){
    *last = current;
    current = current->next;
  }
  if ( !current ) {
    // no free block found
    current = request_space(*last, size);
  }
  return current;
}

struct block_meta *request_space(struct block_meta *last, size_t size){
  struct block_meta *block;
  block = sbrk(0);
  void *request = sbrk(size + META_SIZE);
  assert((void*)block == request); // not thread safe
  if(request == (void*) -1){
    return NULL;
  }

  if(last) { // NULL on first request
    last->next = block;
  }
  block->size = size;
  block->next = NULL;
  block->free = 0;
  block->magic = 0x12345678;
  return block;

}

struct block_meta *get_block_ptr(void *ptr){
  return (struct block_meta*)ptr - 1;
}

void print_block(struct block_meta *block, int first, int last) {
  uint8_t *ptr = (uint8_t*)(block + 1);
  int i,j,flag = 0;
  if ( first ) {
    printf("\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t heap start\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  }
  printf("*-------------------------------------------------*   |\n");
  printf("| addr  -> %014p                         | <-+\n",
          block);
  printf("| size  ->     %#010x                         |\n",
          (unsigned int)block->size);
  printf("| free  ->              %1x                         |\n",
          (unsigned int)block->free);
  printf("| magic ->     %#010x                         |\n",
          (unsigned int)block->magic);
  printf("| next  -> %014p                         | --+\n",
          block->next);
  printf("*-------------------------------------------------*   |\n");
  printf("| contents:                                       |   |\n");
  printf("|  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f |   |\n| ");
  // print contents
  for ( i=0; i < min(block->size, 0x50); i += 0x10 ) {
    for ( j=0; j < 0x10; j++ ) {
      if ( (i+j) >= min(block->size, 0x50)) {
        // don't overreach into further memory segments
        flag = 1;
        break;
      }
      printf("%02x ", ptr[i+j]);
    }
    if ( flag ) {
      // pad out with spaces for incomplete lines
      for ( j=0; j < ( 0x10 - (block->size % 0x10) ); j++ ) {
        printf("   ");
      }
    }
    printf("|   |\n| ");
  }
  printf("                                                |   |\n");
  printf("*-------------------------------------------------*   |\n");
}

void show_heap() {
  struct block_meta *current;
  int first, last;
  for ( current = (struct block_meta*) global_base;
      current;
      current = current->next ) {
    first = (current == global_base);
    last = current->next == NULL ? 0 : 1;
    print_block(current, first, last);
  }
}

