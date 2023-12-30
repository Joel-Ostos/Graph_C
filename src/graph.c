#include "graph.h"
#include <string.h> 
#define INITIAL_SIZE 123
#define RESIZE_FACTOR 2

static Hashmap* init_hashmap(bool opt, size_t size)
{
  element* el = (element*)calloc(size,sizeof(element));
  if (!el) {perror("Error creating element array"); return NULL;}

  Hashmap* map = (Hashmap*) malloc(sizeof(Hashmap));
  if (!map) {perror("Error creating hashmap"); return NULL;}

  if (opt) {
    map->capacity = size;
    map->occupied = 0;
    map->elements = el;
    map->head = NULL;
    map->tail = NULL;
    return map;
  }
  map->capacity = INITIAL_SIZE;
  map->occupied = 0;
  map->elements = el;
  map->head = NULL;
  map->tail = NULL;
  return map;
}

static uint32_t hash(unsigned char* str, size_t size)
{
    uint32_t hash = 5381;
    size_t c = -1;

    while (c++ < size) {
      hash = ((hash << 5) + hash) + str[c]; 
    }

    return hash;
}

static void resize_hashmap(Hashmap* map)
{
  map->elements = (element*) realloc(map->elements, sizeof(element)* (map->capacity*RESIZE_FACTOR));
  map->capacity *= RESIZE_FACTOR;
  for (element* i = map->head; i->key != NULL; i = i->next) {
    put_hashmap_element(map, i->key, i->size);
    i->key = NULL;
  }
}

static void put_hashmap_element(Hashmap* map, char* key, size_t size)
{
  if (map->capacity == map->occupied) resize_hashmap(map);
  uint32_t index = hash((unsigned char*)key, size) % map->capacity;
  Hashmap* n = init_hashmap(false, 0);
  Vertex v = {.label = key, .neighbours = n, .degree = 0, .n_edges = 0, .n_neighbours = 0};
  element el = {.key = key, .size = size, .value = v, .next = NULL};
  if (map->occupied == 0) {
    map->elements[index] = el;
    map->tail->next = &map->elements[index];
    map->tail = &map->elements[index];
    map->head = &map->elements[index];
    map->occupied++;
  }
  while (map->elements[index].key != NULL) 
    index++;
  if (map->elements[index].key == NULL) {
    map->elements[index] = el;
    map->tail->next = &map->elements[index];
    map->tail = &map->elements[index];
    map->occupied++;
    return;
  }
  resize_hashmap(map);
}

static Vertex get_hashmap_element(Hashmap* map, char* key, size_t size)
{
  uint32_t index = hash((unsigned char*)key, size) % map->capacity;
  if (strcmp(map->elements[index].key, key) == 0) {
    return map->elements[index].value;
  }
  for (element* i = &map->elements[index]; i->key != NULL; i = i->next) {
    if (strcmp(i->key,key) == 0) {
      return i->value;
    }
  }
  printf("\nNot found\n");
}

static void delete_hashmap_element(Hashmap* map, char* key, size_t size)
{
  uint32_t index = hash((unsigned char*)key, size) % map->capacity;
  if (strcmp(map->elements[index].key, key) == 0) {
    map->elements[index].key = NULL;
    return;
  }
  for (element* i = &map->elements[index]; i->key != NULL; i = i->next) {
    if (strcmp(i->key,key) == 0) {
      i->key = NULL;
      return;
    }
  }
}

static bool deinit_hashmap(Hashmap* map)
{
  free(map->elements);
  free(map);
  return true;
}
