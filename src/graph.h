// TODO: Evaluar la posibilidad de hacer que en vez de usar ArrayList_ArrayList_int usemos ArrayList_ArrayList_vertex y por ende crear una estructura aparte para los vértices, con propiedades únicas.
#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "data_structures.h" 
#include <stdio.h>
#include <stdlib.h>

typedef struct Graph Graph;	
typedef struct Vertex Vertex;	

hashmap(Vertex)					

struct Vertex {
  char* label;
  Hashmap_Vertex neighbours;
  size_t degree;
  size_t n_edges;
  size_t n_neighbours;
};						

struct Graph {				
  Hashmap_Vertex adj_matrix;				
  size_t degree;
  size_t n_edges;
  size_t n_vertex;
};						

Graph* init_graph(size_t size);
Vertex add_vertex(Graph** g, char* label);
Vertex add_edge(Graph** g, char* src, char* dst);
void cut_edge(Graph** g, char* src, char* dst);
void dfs(Graph** g, char* src, char* dst);
void bfs(Graph** g, char* src, char* dst);
void dijsktra(Graph** g, char* src, char* dst);
void find_independent_sets(Graph** g, char* src, char* dst);
void minimun_coloring_vertex(Graph** g, char* src, char* dst);
void minimun_expansion_tree(Graph** g);
void deinit_graph(Graph** g);

#endif
