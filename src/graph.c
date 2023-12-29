#include "graph.h"
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

static void resize_hashmap(Hashmap* map);

static void put_hashmap_element(Hashmap* map, char* key, size_t size)
{
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
  return map->elements[index].value;
}
static void delete_hashmap_element(Hashmap* map);
