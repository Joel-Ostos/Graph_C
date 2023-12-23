// TODO: Evaluar la posibilidad de hacer que en vez de usar ArrayList_ArrayList_int usemos ArrayList_ArrayList_vertex y por ende crear una estructura aparte para los vértices, con propiedades únicas.
#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "data_structures.h" 
#include <stdio.h>

arraylist(int)
arraylist(ArrayList_int)
extension(int)

typedef struct Directed_Graph Directed_Graph;
typedef struct Undirected_Graph Undirected_Graph;
struct Directed_Graph {
  size_t n_vertex;
  size_t n_edges;
  ArrayList_ArrayList_int adjacency_list;
};

struct Undirected_Graph {
  size_t n_vertex;
  size_t n_edges;
  ArrayList_ArrayList_int adjacency_matrix;
};

extern Directed_Graph init_Directed_Graph(size_t n_vertex)
{
  ArrayList_ArrayList_int adjacency_list = init_array_ArrayList_int(10);
  for (size_t i = 0; i < n_vertex; i++) {
    ArrayList_int tmp = init_array_int(1);
    push_back_arraymatrix_int(&adjacency_list, &tmp, true);
  }
  return (Directed_Graph) {
    n_vertex,
    0,
    adjacency_list,
  };
}

extern Undirected_Graph init_Undirected_Graph(size_t n_vertex)
{
  ArrayList_ArrayList_int adjacency_matrix = init_array_ArrayList_int(10);
  for (size_t i = 0; i < n_vertex; i++) {
    ArrayList_int tmp = init_array_int(n_vertex);
    for (size_t j = 0; j < n_vertex; j++) {
      push_back_array_int(&tmp, 0);
    }
    push_back_arraymatrix_int(&adjacency_matrix, &tmp, true);
  }
  return (Undirected_Graph) {
    n_vertex,
    0,
    adjacency_matrix,
  };
}

bool add_vertex_Directed_Graph(Directed_Graph* graph)
{
  ArrayList_int tmp = init_array_int(1);
  push_back_arraymatrix_int(&graph->adjacency_list, &tmp, true);
}

bool add_vertex_Undirected_Graph(Undirected_Graph* graph)
{
  ArrayList_int tmp = init_array_int(graph->n_vertex);
  for (size_t j = 0; j < graph->n_vertex; j++) {
    push_back_array_int(&tmp, 0);
  }
  push_back_arraymatrix_int(&graph->adjacency_matrix, &tmp, true);
}

bool add_edge_Directed_Graph(Directed_Graph* graph, int index_1, int index_2)
{
  push_back_array_int(&graph->adjacency_list.array[index_1], index_2);
  graph->n_edges++;
}

bool add_edge_Undirected_Graph(Undirected_Graph* graph, int index_1, int index_2)
{
  graph->adjacency_matrix.array[index_1].array[index_2]+=1;
  graph->adjacency_matrix.array[index_2].array[index_1]+=1;
  graph->n_edges++;
}

#endif
