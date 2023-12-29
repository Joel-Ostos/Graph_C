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

struct Hashmap {
  size_t capacity;
  size_t occupied;
  element* elements;
  element* head;
  element* tail;
};

struct Vertex {
  char* label;
  size_t label_size;
  Hashmap* neighbours;
  size_t degree;
  size_t n_edges;
  size_t n_neighbours;
};						
struct element {
  char* key;
  size_t size;
  Vertex value;
  element* next;
};


struct Graph {				
  Hashmap adj_matrix;				
  size_t degree;
  size_t n_edges;
  size_t n_vertex;
};						

static Hashmap* init_hashmap(bool opt, size_t size);
static void resize_hashmap(Hashmap* map);
static uint32_t hash(unsigned char* str, size_t size);
static void put_hashmap_element(Hashmap* map, char* key, size_t size);
static Vertex get_hashmap_element(Hashmap* map, char* key, size_t size);
static void delete_hashmap_element(Hashmap* map);
Graph* init_graph(size_t size);
Vertex add_vertex(Graph* g, char* label);
Vertex add_edge(Graph* g, char* src, char* dst);
void cut_edge(Graph* g, char* src, char* dst);
void dfs(Graph* g, char* src, char* dst);
void bfs(Graph* g, char* src, char* dst);
void dijsktra(Graph* g, char* src, char* dst);
void find_independent_sets(Graph* g, char* src, char* dst);
void minimun_coloring_vertex(Graph* g, char* src, char* dst);
void minimun_expansion_tree(Graph* g);
void deinit_graph(Graph* g);

#endif
