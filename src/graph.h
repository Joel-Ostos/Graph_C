#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils/data_structures.h"

typedef struct graph Graph;	
typedef struct vertex Vertex;	
typedef struct edge Edge;	
typedef struct traversal Traversal;

struct vertex {
  char* label;
  size_t label_size;
  HashMap* edges;
  size_t degree;
  size_t n_edges;
  int color;
  Vertex* parent;
};						

struct edge {
  Vertex* vertex;
  size_t length;
};						

struct graph {				
  HashMap* adj_matrix;				
  size_t degree;
  size_t n_edges;
  size_t n_vertex;
  size_t (*hash)(const char* str, size_t size);
};						

Graph* init_graph(size_t (*hash)(const char* str, size_t size));
Graph* complete_graph(size_t (*hash)(const char* str, size_t size), int n);
bool add_vertex(Graph* g, const char* label, size_t label_size);
bool add_edge(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst, int dist);
bool cut_edge(Graph* g, char* src, char* dst);
void print_graph(Graph* g);
ArrayList* dfs(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst);
ArrayList* bfs(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst);
void print_traversal(ArrayList* result);
void deinit_traversal(ArrayList* result);
void dijsktra(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst);
void find_independent_sets(Graph* g, char* src, char* dst);
int chromatic_number(Graph* g);
void minimun_expansion_tree(Graph* g);
void deinit_graph(Graph* g);

#endif
