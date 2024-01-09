// TODO: Evaluar la posibilidad de hacer que en vez de usar ArrayList_ArrayList_int usemos ArrayList_ArrayList_vertex y por ende crear una estructura aparte para los vértices, con propiedades únicas.
#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct Graph Graph;	
typedef struct Vertex Vertex;	
typedef struct Hashmap Hashmap;
typedef struct element element;
typedef struct Hashmap_ptr Hashmap_ptr;
typedef struct inner_element inner_element;
typedef struct traversal traversal;

struct Hashmap {
  size_t capacity;
  size_t occupied;
  element* elements;
  element* head;
  element* tail;
};

struct Hashmap_ptr {
  size_t capacity;
  size_t occupied;
  inner_element* elements;
  inner_element* head;
  inner_element* tail;
};

struct Vertex {
  char* label;
  size_t label_size;
  Hashmap_ptr* neighbours;
  size_t degree;
  size_t n_edges;
  size_t n_neighbours;
  int color;
};						

struct element {
  char* key;
  size_t size;
  Vertex value;
  element* next;
  element* parent;
  bool state;
};

struct inner_element {
  char* key;
  size_t size;
  element* value;
  inner_element* next;
};

struct Graph {				
  Hashmap* adj_matrix;				
  size_t degree;
  size_t n_edges;
  size_t n_vertex;
};						

struct traversal {
  size_t size;
  element** elements;
};

static Hashmap* init_hashmap(bool opt, size_t size);
static void resize_hashmap(Hashmap* map);
static int hash(unsigned char* str, size_t size);
static Vertex* put_hashmap_element(Hashmap* map, char* key, size_t size);
static element* get_hashmap_element(Hashmap* map, char* key, size_t size);
static void delete_hashmap_element(Hashmap* map, char* key, size_t size);
static void iterate_hashmap(Hashmap* map);
static void deinit_hashmap(Hashmap* map);

static Hashmap_ptr* init_hashmap_ptr(bool opt, size_t size);
static void resize_hashmap_ptr(Hashmap_ptr* map, Hashmap* src);
static inner_element* put_hashmap_element_ptr(Hashmap* map, char* key, char* dst, size_t size, size_t size_dst);
static inner_element* get_hashmap_element_ptr(Hashmap_ptr* map, char* key, size_t size);
static void delete_hashmap_element_ptr(Hashmap_ptr* map, char* key, size_t size);
static void iterate_hashmap_ptr(Hashmap_ptr* map);
static void deinit_hashmap_ptr(Hashmap_ptr* map);

Graph* init_graph();
Vertex* add_vertex(Graph* g, char* label, size_t size);
void add_edge(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst);
void cut_edge(Graph* g, char* src, char* dst);
void print_graph(Graph* g);
void dfs(Graph* g, char* src, char* dst);
traversal* bfs(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst);
void print_bfs_result(traversal* result);
void deinit_bfs_result(traversal* result);
void dijsktra(Graph* g, char* src, char* dst);
void find_independent_sets(Graph* g, char* src, char* dst);
int chromatic_number(Graph* g);
void minimun_expansion_tree(Graph* g);
void deinit_graph(Graph* g);

#endif
