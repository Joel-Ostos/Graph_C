// TODO: Evaluar la posibilidad de hacer que en vez de usar ArrayList_ArrayList_int usemos ArrayList_ArrayList_vertex y por ende crear una estructura aparte para los vértices, con propiedades únicas.
#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "data_structures.h" 
#include <stdio.h>

arraylist(int)
arraylist(ArrayList_int)
typedef struct Vertex Vertex;
typedef struct Directed_Graph Directed_Graph;
typedef struct Undirected_Graph Undirected_Graph;
struct Vertex {
  char[20] label;
  int degree;
  ArrayList_Vertex* adjacent_vertex;
};
arraylist(Vertex)
arraylist(ArrayList_Vertex)
extension(Vertex)

struct Directed_Graph {
  size_t n_vertex;
  size_t n_edges;
  int max_coloring;
  int degree;
  ArrayList_Vertex adjacency_list;
};

struct Undirected_Graph {
  size_t n_vertex;
  size_t n_edges;
  int max_coloring;
  int degree;
  ArrayList_Vertex vertex_list;
  ArrayList_ArrayList_int adjacency_matrix;
};

// Defining the arraylist data structure to store the elements

static Vertex Vertex_init(const char vertex_label[20], ArrayList_Vertex* adj_vertex)
{
  return (Vertex) {
   vertex_label,
   0,
   adj_vertex,
  }
}

extern Directed_Graph init_Directed_Graph(size_t n_vertex)
{
  ArrayList_Vertex adjacency_list = init_array_Vertex(n_vertex);
  return (Directed_Graph) {
    n_vertex,
    0,
    adjacency_list,
    -1,
    -1,
  };
}

extern Undirected_Graph init_Undirected_Graph(size_t n_vertex)
{
  ArrayList_ArrayList_Vertex vertex_list = init_array_ArrayList_Vertex(n_vertex);
  ArrayList_ArrayList_int adjacency_matrix = init_array_ArrayList_Vertex(n_vertex);
  return (Undirected_Graph) {
    n_vertex,
    0,
    vertex_list,
    adjacency_matrix,
    -1,
    -1,
  };
}

bool add_vertex_Directed_Graph(Directed_Graph* graph, const char vertex_label[20])
{
  ArrayList_vertex tmp = init_array_Vertex(1);
  vertex v_tmp = Vertex_init(const char[20] vertex_label, &tmp);
  push_back_array_vertex(&graph->adjacency_list, &v_tmp);
}

bool add_vertex_Undirected_Graph(Undirected_Graph* graph, const char vertex_label[20])
{
  ArrayList_int tmp = init_array_int(graph->n_vertex);
  ArrayList_vertex a_tmp = init_array_Vertex(graph->n_vertex);
  vertex v_tmp = Vertex_init(const char[20] vertex_label, &a_tmp);
  for (size_t j = 0; j < graph->n_vertex; j++) {
    push_back_array_int(&tmp, 0);
  }
  push_back_arraymatrix_int(&graph->adjacency_matrix, &tmp, true);
  push_back_array_Vector(&graph->vertex_list, &v_tmp);
}

bool add_edge_Directed_Graph(Directed_Graph* graph, const char[20] name_1, const char[20] name_2)
{
  push_back_array_Vector(&graph->adjacency_list.array[find_index(name_1)], find_vertex(name2));
  find_vertex(name_1).degree +=1;
  graph->n_edges++;
}

bool add_edge_Undirected_Graph(Undirected_Graph* graph, const char[20] name1, const char[20] name_2)
{
  graph->adjacency_matrix.array[find_index(graph, name_1)].array[find_index(graph, name_2)]+=1;
  graph->adjacency_matrix.array[find_index(graph, name_2)].array[find_index(graph, name_1)]+=1;
  push_back_array_Vector(&find(graph, name_1),find(graph, name_2));
  push_back_array_Vector(&find(graph, name_2),find(graph, name_1));
  find(graph, name_1).degree+=1;
  find(graph, name_2).degree+=1;
  graph->n_edges++;
}

#endif
