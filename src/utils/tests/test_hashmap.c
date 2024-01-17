#include "data_structures.h"
#include <stdlib.h>
#include <stdio.h>

size_t hash_a(const char* str, size_t size) {
  int hash = 5381;
  size_t c = 0;
  while (c < size) {
    hash = ((hash << 5) + hash) + str[c]; 
    c++;
  }
  return hash;
}

int main(void) {
  HashMap* mimap = init_hashmap(false, 0, &hash_a);
  for (int i = 0; i < 100; i++) {
    int length = snprintf( NULL, 0, "%d", i );
    char str[length];
    snprintf(str, length + 1, "%d", i );
    hashmap_put(mimap, str, length, (void*) &i, sizeof(*str) * length, sizeof(i));
  }
  for (int i = 0; i < 100; i++) {
    int length = snprintf(NULL, 0, "%d", i);
    char str[length];
    snprintf(str, length + 1, "%d", i );
    printf("%d %s\n", *(int*)hashmap_get(mimap, str, length), str);
  }
  deinit_hashmap(mimap);
}
