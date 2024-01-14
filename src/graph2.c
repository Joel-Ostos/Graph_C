#include <stdlib.h>
#include <string.h> 
#include <assert.h> 
#include "graph.h"
#include "utils/data_structures.h"

#define INITIAL_SIZE 123
#define RESIZE_FACTOR 2

// Graph functions, ready, set go!
Graph* init_graph(size_t (*hash)(const char* str, size_t size)) {
  Graph* g = (Graph*) malloc(sizeof(Graph));
  g->adj_matrix = init_hashmap(false, 0, hash);
  g->degree = 0;
  g->n_edges = 0;
  g->n_vertex = 0;
  return g;
}

//Graph* complete_graph(int n)
//{
//  Graph* g = init_graph();
//  for (int i = 0; i < n; i++) {
//    int length = snprintf( NULL, 0, "%d", i );
//    char* str = malloc( length + 1 );
//    snprintf( str, length + 1, "%d", i );
//    add_vertex(g, str, length);
//    free(str);
//  }
//  for (element* i = g->adj_matrix->head; i != NULL; i = i->next) {
//    for (element* j = i->next; j != NULL; j = j->next) {
//      add_edge(g, i->value.label, i->size, j->value.label, j->size, 0);
//    }
//  }
//  return g;
//}

bool add_vertex(Graph* g, const char* label, size_t label_size)
{
  Vertex v = {.label = (char*) label, .label_size = label_size, .degree = 0, .n_edges = 0, .color = 0};
  v.edges = init_hashmap(false, 0, g->hash);
  if (hashmap_put(g->adj_matrix, (const void*) label, label_size, (void*) &v, sizeof(*label) * label_size, sizeof(v))) {
    g->n_vertex++;
    return true;
  }
  return false;
}

bool add_edge(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst, int dist)
{
  void*  v_1 = hashmap_get(g->adj_matrix, (const void*) src, size_src);
  assert(v_1 != NULL);
  if (v_1 == NULL) exit(1);
  assert(g->hash != NULL);
  ((Vertex*)v_1)->edges->hash_func = g->hash;
  void*  v_2 = hashmap_get(g->adj_matrix, (const void*) dst, size_dst);
  assert(v_2 != NULL);
  if (v_2 == NULL) exit(1);
  ((Vertex*)v_2)->edges->hash_func = g->hash;
  Edge e_1 = {.vertex = (Vertex*) v_1, .length = dist};
  Edge e_2 = {.vertex = (Vertex*) v_2, .length = dist};
  if (hashmap_put(((Vertex*)v_1)->edges, (const void*) dst, size_dst, (void*) &e_2, sizeof(*src) * size_src, sizeof(Edge)) &&
      hashmap_put(((Vertex*)v_2)->edges, (const void*) src, size_src, (void*) &e_1, sizeof(*dst) * size_dst, sizeof(Edge))) {
    return true;
    g->n_edges++;
  }
  return false;
}


//void cut_edge(Graph* g, char* src, char* dst);
//void contract_edge(Graph* g, char* src, char* dst);
//
//traversal* dfs(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst)
//{
//  Stack_element S = init_stack_element();
//  element* source = get_hashmap_element(g->adj_matrix, src, size_src);
//  source->parent = source;
//  element* dest = get_hashmap_element(g->adj_matrix, dst, size_dst);
//  if (source == NULL || dest == NULL) return NULL;
//  push_stack_element(&S, source);
//  while (!empty_stack_element(&S)) {
//    element* actual =  pop_stack_element(&S);
//    for (inner_element* i = actual->value.neighbours->head; i != NULL; i = i->next) {
//      if (i->value->parent != NULL) continue;
//      push_stack_element(&S, i->value);
//      i->value->parent = actual;
//    }
//    if (dest->parent != NULL) {
//      break;
//    }
//  }
//  if (dest->parent == NULL) {
//    printf("Path not found");
//    return NULL;
//  };
//  int cont = 1;
//  for (element* i = dest; i != source; i = i->parent) {
//    cont++;
//  }
//  element** arr = (element**) malloc(sizeof(element*)*(cont+1));
//  traversal* el = (traversal*) malloc(sizeof(traversal));
//  el->elements = arr;
//  el->size = cont;
//  int j = cont-1;
//  for (element* i = dest; j >= 0; i = i->parent, j--) {
//    arr[j] = i;
//  }
//  for (element* b = g->adj_matrix->head; b != NULL; b = b->next) {
//    b->parent = NULL;
//  }
//  deinit_stack_element(&S);
//  return el;
//}
//
ArrayList* bfs(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst)
{
  Queue* Q = init_queue(20);
  Vertex* source = hashmap_get(g->adj_matrix, (const void*) src, size_src) != NULL
    ? (Vertex*) hashmap_get(g->adj_matrix, (const void*) src, size_src) 
    : NULL;
  Vertex* dest = hashmap_get(g->adj_matrix, (const void*) dst, size_dst) != NULL
    ? (Vertex*) hashmap_get(g->adj_matrix, (const void*) dst, size_dst) 
    : NULL;
  if (source == NULL || dest == NULL) return NULL;
  source->parent = source;
  queue_push(Q, (void*) source);
  while (!queue_empty(Q)) {
    Vertex* actual = (Vertex*) queue_pop(Q);
    assert(actual != NULL);
    for (Element* i = actual->edges->head; i != NULL; i = i->next) {
      if (((Edge*)i->value)->vertex->parent != NULL) continue;
      queue_push(Q, (void*)((Edge*)i->value)->vertex);
      ((Edge*)i->value)->vertex->parent = actual;
    }
    if (dest->parent != NULL) {
      break;
    }
  }
  if (dest->parent == NULL) {
    printf("Path not found");
    return NULL;
  };
  ArrayList* arraylist = init_array(g->n_vertex);
  for (Vertex* i = dest; i != source; i = i->parent) {
    array_push_back(arraylist, (void*) i);
  }
  array_push_back(arraylist, (void*) source);
  for (Element* b = g->adj_matrix->head; b != NULL; b = b->next) {
    ((Vertex*)b->value)->parent = NULL;
  }
  deinit_queue(Q);
  return arraylist;
}

ArrayList* dfs(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst)
{
  Stack* S = init_stack(20);
  Vertex* source = hashmap_get(g->adj_matrix, (const void*) src, size_src) != NULL
    ? (Vertex*) hashmap_get(g->adj_matrix, (const void*) src, size_src) 
    : NULL;
  Vertex* dest = hashmap_get(g->adj_matrix, (const void*) dst, size_dst) != NULL
    ? (Vertex*) hashmap_get(g->adj_matrix, (const void*) dst, size_dst) 
    : NULL;
  if (source == NULL || dest == NULL) return NULL;
  source->parent = source;
  stack_push(S, (void*) source);
  while (!stack_empty(S)) {
    Vertex* actual = (Vertex*) stack_pop(S);
    assert(actual != NULL);
    for (Element* i = actual->edges->head; i != NULL; i = i->next) {
      if (((Edge*)i->value)->vertex->parent != NULL) continue;
      stack_push(S, (void*)((Edge*)i->value)->vertex);
      ((Edge*)i->value)->vertex->parent = actual;
    }
    if (dest->parent != NULL) {
      break;
    }
  }
  if (dest->parent == NULL) {
    printf("Path not found");
    return NULL;
  };
  ArrayList* arraylist = init_array(g->n_vertex);
  for (Vertex* i = dest; i != source; i = i->parent) {
    array_push_back(arraylist, (void*) i);
  }
  array_push_back(arraylist, (void*) source);
  for (Element* b = g->adj_matrix->head; b != NULL; b = b->next) {
    ((Vertex*)b->value)->parent = NULL;
  }
  deinit_stack(S);
  return arraylist;
}

//void dijsktra(Graph* g, char* src, size_t size_src, char* dst, size_t size_dst)
//{
//}
//
//void find_independent_sets(Graph* g, char* src, char* dst);
//void minimun_expansion_tree(Graph* g);
//
//void print_traversal_result(traversal* result)
//{
//  printf("\n");
//  for (size_t i = 0; i < result->size; i++) {
//    printf("%s ", result->elements[i]->value.label);
//  }
//}
//
bool find_valid_number(int* arr, size_t size, int el)		
{									
  for (size_t i = 0; i < size; i++) {
    if (el == arr[i]) {						
      return false;							
    }									
  }									
  return true;								
}									

int chromatic_number(Graph* g) {
  int chromatic = 0;
  for (Element* i = g->adj_matrix->head; i != NULL && i->key != NULL; i = i->next) {
    int colors[g->n_vertex];
    for (size_t l = 0; l < g->n_vertex; l++) colors[l] = 0;
    int p = 0;
    for (Element* j = ((Vertex*)i->value)->edges->head; j != NULL; j = j->next) {
      if ( ((Edge*)j->value)->vertex->color > -1) {
	colors[p] = ((Edge*)j->value)->vertex->color;
	p++;
      }
    }
    for (int k = 1;; k++) {
      if (colors[0] == 0) {
	((Vertex*)i->value)->color = 1;
	break;
      }
      if (find_valid_number(colors, g->n_vertex, k)) {
	((Vertex*)i->value)->color = k;
	if (k > chromatic) chromatic = k;
	break;
      }
    }
  }
  return chromatic;
}

void print_graph(Graph* g) {
  printf("\n");
  for (Element* i = g->adj_matrix->head; i != NULL && i->key != NULL; i = i->next) {
    printf("{");
    printf("{%s}", ((Vertex*)i->value)->label);
    for (Element* j = ((Vertex*)i->value)->edges->head;  j != NULL; j = j->next) {
      printf(" %s", ((Edge*)j->value)->vertex->label);
    }
    printf("}\n");
  }
}

void print_traversal(ArrayList* result) {
  assert(result != NULL);
  printf("\n{");
  for (int i = result->occupied-1; i >= 0; i--) {
    printf("%s ", ((Vertex*)result->array[i])->label);
  }
  printf("}\n");
}

void deinit_traversal(ArrayList* result) {
  deinit_array(result);
}

void deinit_graph(Graph* g)
{
  for (Element* i = g->adj_matrix->head; i != NULL ; i = i->next) {
    deinit_hashmap(((Vertex*)i->value)->edges);
  }
  deinit_hashmap(g->adj_matrix);
  free(g);
}
