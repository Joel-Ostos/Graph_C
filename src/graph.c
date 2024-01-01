#include "graph.h"
#include <string.h> 
#define INITIAL_SIZE 123
#define RESIZE_FACTOR 2

static Hashmap* init_hashmap (bool opt, size_t size)
{
  element* el = (element*) calloc(size,sizeof(element));
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
  size_t c = 0;

  while (c < size) {
    hash = ((hash << 5) + hash) + str[c]; 
    c++;
  }

  return hash;
}

static void resize_hashmap(Hashmap* map)
{
  if (map->capacity == 0) exit(1);
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
  Hashmap_ptr* n = init_hashmap_ptr(false, 0);
  if (map->elements[index].key != NULL) {
    if (strcmp(map->elements[index].key, key) == 0) {
      return;
    }
  }
  Vertex v = {.label = key, .neighbours = n, .degree = 0, .n_edges = 0, .n_neighbours = 0};
  element el = {.key = key, .size = size, .value = v, .next = NULL};
  if (map->occupied == 0) {
    map->elements[index] = el;
    map->tail = &(map->elements[index]);
    map->head = &(map->elements[index]);
    map->head->next = map->tail;
    map->occupied++;
    return;
  }

  while (map->elements[index].key != NULL) {
    index++;
  }
  if (map->elements[index].key == NULL) {
    map->elements[index] = el;
    map->tail->next = &map->elements[index];
    map->tail = &map->elements[index];
    map->occupied++;
    return;
  }
  printf("Cannot put the element");
  return;
}

static element* get_hashmap_element(Hashmap* map, char* key, size_t size)
{
  uint32_t index = hash((unsigned char*)key, size) % map->capacity;
  if (map->elements[index].key != NULL) {
    if (strcmp(map->elements[index].key, key) == 0) {
      return &map->elements[index];
    }
  }
  for (element* i = &map->elements[index]; i->key != NULL; i = i->next) {
    if (strcmp(i->key,key) == 0) {
      return i;
    }
  }
  printf("\nNot found\n");
  return NULL;
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
void iterate_hashmap(Hashmap* map)
{
  element* current = map->head;
  while (current != NULL) {
    printf("%s ", current->key);
    current = current->next;
  }
}

static void deinit_hashmap(Hashmap* map)
{
  free(map->elements);
  free(map);
}

// New
static Hashmap_ptr* init_hashmap_ptr (bool opt, size_t size)
{
  element_ptr* el = (element_ptr*) calloc(size, sizeof(element_ptr));
  if (!el) {perror("Error creating element array"); return NULL;}

  Hashmap_ptr* map = (Hashmap_ptr*) malloc(sizeof(Hashmap_ptr));
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


static void resize_hashmap_ptr(Hashmap_ptr* map, Hashmap* map_src)
{
  if (map->capacity == 0) exit(1);
  map->elements = (element_ptr*) realloc(map->elements, sizeof(element_ptr) * (map->capacity * RESIZE_FACTOR));
  map->capacity *= RESIZE_FACTOR;
  for (element_ptr* i = map->head; i->key != NULL; i = i->next) {
    put_hashmap_element_ptr(map, map_src, i->key, i->size);
    i->key = NULL;
  }
}

static void put_hashmap_element_ptr(Hashmap_ptr* map, const Hashmap* map_src, char* key, size_t size)
{
  if (map->capacity == map->occupied) resize_hashmap_ptr(map, map_src);
  uint32_t index = hash((unsigned char*) key, size) % map->capacity;
  if (map->elements[index].key != NULL) {
    if (strcmp(map->elements[index].key, key) == 0) {
      return;
    }
  }
  element* tmp = get_hashmap_element(map_src, key, size);
  if (!tmp) return;
  Vertex* v = &(tmp->value);
  element_ptr el = {.key = key, .size = size, .value = v, .next = NULL};
  if (map->occupied == 0) {
    map->elements[index] = el;
    map->tail = &(map->elements[index]);
    map->head = &(map->elements[index]);
    map->occupied++;
    return;
  }

  while (map->elements[index].key != NULL) {
    index++;
  }
  if (map->elements[index].key == NULL) {
    map->elements[index] = el;
    map->tail->next = &map->elements[index];
    map->tail = &map->elements[index];
    map->occupied++;
    return;
  }
  printf("Cannot put the element");
  return;
}

static element_ptr* get_hashmap_element_ptr(Hashmap_ptr* map, char* key, size_t size)
{
  uint32_t index = hash((unsigned char*)key, size) % map->capacity;
  if (map->elements[index].key != NULL) {
    if (strcmp(map->elements[index].key, key) == 0) {
      return &map->elements[index];
    }
  }
  for (element_ptr* i = &map->elements[index]; i->key != NULL; i = i->next) {
    if (strcmp(i->key,key) == 0) {
      return i;
    }
  }
  printf("\nNot found\n");
  return NULL;
}

static void delete_hashmap_element_ptr(Hashmap_ptr* map, char* key, size_t size)
{
  uint32_t index = hash((unsigned char*)key, size) % map->capacity;
  if (strcmp(map->elements[index].key, key) == 0) {
    map->elements[index].key = NULL;
    return;
  }
  for (element_ptr* i = &map->elements[index]; i->key != NULL; i = i->next) {
    if (strcmp(i->key,key) == 0) {
      i->key = NULL;
      return;
    }
  }
}
void iterate_hashmap_ptr(Hashmap_ptr* map)
{
  element_ptr* current = map->head;
  while (current != NULL) {
    printf("%s ", current->key);
    current = current->next;
  }
}

static void deinit_hashmap_ptr(Hashmap_ptr* map)
{
  free(map->elements);
  free(map);
}

// Graph functions, ready, set go!
Graph* init_graph()
{
  Graph* g = (Graph*) malloc(sizeof(Graph));
  g->adj_matrix = init_hashmap(false,0);
  g->degree = 0;
  g->n_edges = 0;
  g->n_vertex = 0;
  return g;
}

Vertex add_vertex(Graph* g, char* label, size_t label_size)
{
  put_hashmap_element(g->adj_matrix, label, label_size);
  Vertex el = get_hashmap_element(g->adj_matrix, label, label_size)->value;
  el.label = label;
  el.label_size = label_size;
  return el;
}

Vertex* add_edge(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst)
{
  element* el = get_hashmap_element(g->adj_matrix, src, size_src);
  if (!el) return NULL;
  put_hashmap_element_ptr(el->value.neighbours, g->adj_matrix, dst, size_dst);
  el->value.degree += 1;
  printf("%s\n", g->adj_matrix->head->key);
  return &el->value;
}

void print_graph(Graph* g) {
  //printf("%s", g->adj_matrix->head->key);
  //for (element* i = g->adj_matrix->head; i != NULL; i = i->next) {
  //  printf("%s", i->key);
  //}
}

void cut_edge(Graph* g, char* src, char* dst);
void dfs(Graph* g, char* src, char* dst);
void bfs(Graph* g, char* src, char* dst);
void dijsktra(Graph* g, char* src, char* dst);
void find_independent_sets(Graph* g, char* src, char* dst);
void minimun_coloring_vertex(Graph* g, char* src, char* dst);
void minimun_expansion_tree(Graph* g);

void deinit_graph(Graph* g)
{
  deinit_hashmap(g->adj_matrix);
  free(g);
}
