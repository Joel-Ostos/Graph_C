#include "graph.h"
#include "queue.h"
#include <string.h> 
#define INITIAL_SIZE 123
#define RESIZE_FACTOR 2

static Hashmap* init_hashmap(bool opt, size_t size)
{
  Hashmap* map = (Hashmap*) malloc(sizeof(Hashmap));
  if (!map) {perror("Error creating hashmap"); return NULL;}

  if (opt) {
    element* el = (element*) calloc(size,sizeof(element) * size);
    if (!el) {perror("Error creating element array"); return NULL;}
    map->capacity = size;
    map->occupied = 0;
    map->elements = el;
    map->head = NULL;
    map->tail = NULL;
    return map;
  }
  element* el = (element*) calloc(INITIAL_SIZE,sizeof(element)* INITIAL_SIZE);
  if (!el) {perror("Error creating element array"); return NULL;}
  map->capacity = INITIAL_SIZE;
  map->occupied = 0;
  map->elements = el;
  map->head = NULL;
  map->tail = NULL;
  return map;
}

static int hash(unsigned char* str, size_t size)
{
  int hash = 5381;
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
  map->elements = (element*) realloc(map->elements, sizeof(element) * (map->capacity*RESIZE_FACTOR));
  map->capacity *= RESIZE_FACTOR;
  for (element* i = map->head; i->key != NULL; i = i->next) {
    put_hashmap_element(map, i->key, i->size);
    i->key = NULL;
  }
}

static Vertex* put_hashmap_element(Hashmap* map, char* key, size_t size)
{
  if (map->capacity == map->occupied) resize_hashmap(map);
  int index = hash((unsigned char*)key, size) % map->capacity;
  Hashmap_ptr* n = init_hashmap_ptr(false, 0);
  if (map->elements[index].key != NULL) {
    if (strcmp(map->elements[index].key, key) == 0) {
      return NULL;
    }
  }
  Vertex v = {.label = key, .neighbours = n, .degree = 0, .n_edges = 0};
  element el = {.key = key, .size = size, .value = v, .parent = NULL, .next = NULL};
  if (map->occupied == 0) {
    map->elements[index] = el;
    map->tail = &(map->elements[index]);
    map->head = &(map->elements[index]);
    map->occupied++;
    return &(map->elements[index].value);
  }

  while (map->elements[index].key != NULL) {
    index++;
  }
  if (map->elements[index].key == NULL) {
    map->elements[index] = el;
    map->tail->next = &map->elements[index];
    map->tail = &map->elements[index];
    map->occupied++;
    return &(map->elements[index].value);
  }
  printf("Cannot put the element\n");
  return NULL;
}

static element* get_hashmap_element(Hashmap* map, char* key, size_t size)
{
  int index = hash((unsigned char*)key, size) % map->capacity;
  if (map->elements[index].key != NULL) {
    if (strcmp(map->elements[index].key, key) == 0) {
      return &map->elements[index];
    }
  }
  for (element* i = map->head; i != NULL && i->key != NULL; i = i->next) {
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
  Hashmap_ptr* map = (Hashmap_ptr*) malloc(sizeof(Hashmap_ptr));
  if (!map) {perror("Error creating hashmap"); return NULL;}

  if (opt) {
    inner_element* el = (inner_element*) calloc(size, sizeof(inner_element)*size);
    if (!el) {perror("Error creating element array"); return NULL;}
    map->capacity = size;
    map->occupied = 0;
    map->elements = el;
    map->head = NULL;
    map->tail = NULL;
    return map;
  }
  inner_element* el = (inner_element*) calloc(INITIAL_SIZE, sizeof(inner_element)*INITIAL_SIZE);
  if (!el) {perror("Error creating element array"); return NULL;}
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
  map->elements = (inner_element*) realloc(map->elements, sizeof(inner_element) * (map->capacity * RESIZE_FACTOR));
  map->capacity *= RESIZE_FACTOR;
  for (inner_element* i = map->head; i->key != NULL; i = i->next) {
    put_hashmap_element_ptr(map_src, i->key, i->key, i->size, i->size);
    i->key = NULL;
  }
}

static inner_element* put_hashmap_element_ptr(Hashmap* map_src, char* key, char* dst, size_t size, size_t size_dst)
{
  element* el_1 = get_hashmap_element(map_src, key, size);
  element* el_2 = get_hashmap_element(map_src, dst, size_dst);
  if (el_1 == NULL || el_2 == NULL) return NULL;
  Hashmap_ptr* map = el_1->value.neighbours;
  if (map->capacity == map->occupied) resize_hashmap_ptr(map, map_src);
  int index = hash((unsigned char*) key, size) % map->capacity;
  if (map->elements[index].key != NULL && key != NULL) {
    if (strcmp(map->elements[index].key, key) == 0) {
      return NULL;
    }
  }
  inner_element el = {.key = dst , .size = el_2->size, .value = el_2, .next = NULL};
  if (map->occupied == 0) {
    map->elements[index] = el;
    map->tail = &(map->elements[index]);
    map->head = &(map->elements[index]);
    map->occupied++;
    return &(map->elements[index]);
  }

  while (map->elements[index].key != NULL) {
    index++;
  }
  if (map->elements[index].key == NULL) {
    map->elements[index] = el;
    map->tail->next = &map->elements[index];
    map->tail = &map->elements[index];
    map->occupied++;
    return &(map->elements[index]);
  }
  printf("Cannot put the element\n");
  return NULL;
}

static inner_element* get_hashmap_element_ptr(Hashmap_ptr* map, char* key, size_t size)
{
  uint32_t index = hash((unsigned char*)key, size) % map->capacity;
  if (map->elements[index].key != NULL) {
    if (strcmp(map->elements[index].key, key) == 0) {
      return &map->elements[index];
    }
  }
  for (inner_element* i = &map->elements[index]; i->key != NULL; i = i->next) {
    if (strcmp(i->key, key) == 0) {
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
  for (inner_element* i = &map->elements[index]; i->key != NULL; i = i->next) {
    if (strcmp(i->key,key) == 0) {
      i->key = NULL;
      return;
    }
  }
}
void iterate_hashmap_ptr(Hashmap_ptr* map)
{
  inner_element* current = map->head;
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

Vertex* add_vertex(Graph* g, char* label, size_t label_size)
{
  return put_hashmap_element(g->adj_matrix, label, label_size);
}

void add_edge(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst)
{
  put_hashmap_element_ptr(g->adj_matrix, src, dst, size_src, size_dst);
}

void print_graph(Graph* g) {
  for (element* i = g->adj_matrix->head; i != NULL && i->key != NULL; i = i->next) {
    printf("{%s", i->key);
    for (inner_element* j = i->value.neighbours->head; j != NULL && j->key != NULL; j = j->next) {
      printf(", %s", j->key);
    }
    printf("}\n");
  }
}

void cut_edge(Graph* g, char* src, char* dst);

traversal* bfs(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst)
{
  Queue_element Q = init_Queue_element();
  element* source = get_hashmap_element(g->adj_matrix, src, size_src);
  element* dest = get_hashmap_element(g->adj_matrix, dst, size_dst);
  if (source == NULL || dest == NULL) {
    return NULL;
  }
  Queue_element_push(&Q, source);
  while (!Queue_element_empty(&Q)) {
    element* actual =  Queue_element_pop(&Q);
    for (inner_element* i = actual->value.neighbours->head; i != NULL; i = i->next) {
      if (i->value->parent!=NULL) continue;
      Queue_element_push(&Q, i->value);
      i->value->parent = actual;
    }
  }
  if (dest->parent == NULL) {
    printf("Path not found");
    return NULL;
  };
  size_t cont = 0;
  for (element* i = dest; i != NULL; i = i->parent) {
    cont++;
  }
  element** arr = (element**) malloc(sizeof(element*)*cont);
  traversal* el = (traversal*) malloc(sizeof(traversal));
  el->elements = arr;
  el->size = cont;
  element* i = dest;
  size_t j = 0;
  for (; i != NULL && j < cont; i = i->parent, j++) {
    arr[j] = i;
  }
  deinit_Queue_element(&Q);
  return el;
}

void dfs(Graph* g, char* src, char* dst);
void dijsktra(Graph* g, char* src, char* dst);
void find_independent_sets(Graph* g, char* src, char* dst);
void minimun_coloring_vertex(Graph* g, char* src, char* dst);
void minimun_expansion_tree(Graph* g);

void deinit_graph(Graph* g)
{
  for (element* i = g->adj_matrix->head; i != NULL && i->key != NULL; i = i->next) {
    free(i->value.neighbours->elements);
    free(i->value.neighbours);
  }
  free(g->adj_matrix->elements);
  free(g->adj_matrix);
  free(g);
}
