#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils/data_structures.h"

typedef struct uw_graph UW_Graph;	
typedef struct w_graph W_Graph;	
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
  bool visited;
  size_t dist;
};						

struct edge {
  Vertex* vertex;
  size_t length;
};						

struct w_graph {				
  HashMap* adj_matrix;				
  size_t degree;
  size_t n_edges;
  size_t n_vertex;
  size_t (*hash)(const char* str, size_t size);
};						

struct uw_graph {				
  HashMap* adj_matrix;				
  size_t degree;
  size_t n_edges;
  size_t n_vertex;
  size_t (*hash)(const char* str, size_t size);
};						

UW_Graph* init_uw_graph(size_t (*hash)(const char* str, size_t size));
W_Graph* init_w_graph(size_t (*hash)(const char* str, size_t size));
UW_Graph* complete_graph(size_t (*hash)(const char* str, size_t size), int n);
bool add_vertex(UW_Graph* g, W_Graph* g2, const char* label, size_t label_size);
bool add_edge(UW_Graph* g, W_Graph* g2, char* src, size_t size_src, char* dst, size_t size_dst, int dist);
void cut_edge(UW_Graph* g, char* src, size_t size_src, char* dst, size_t size_dst);
void print_graph(UW_Graph* g, W_Graph* g2);
ArrayList* dfs(UW_Graph* g, char* src, size_t size_src, char* dst, size_t size_dst);
ArrayList* bfs(UW_Graph* g, char* src, size_t size_src, char* dst, size_t size_dst);
void print_traversal(ArrayList* result);
void deinit_traversal(ArrayList* result);
ArrayList* dijsktra(W_Graph* g, char* src, size_t size_src, char* dst, size_t size_dst);
void find_independent_sets(UW_Graph* g, W_Graph* g2, char* src, char* dst);
int chromatic_number(UW_Graph* g, W_Graph* g2);
void minimun_expansion_tree(UW_Graph* g, W_Graph* g2);
void deinit_graph(UW_Graph* g, W_Graph* g2);

#endif
