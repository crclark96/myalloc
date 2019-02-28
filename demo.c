#include "malloc.h"

int main() {
  void *ptr0 = malloc(16);
  show_heap();
  free(ptr0);
  show_heap();
  return 0;
}
