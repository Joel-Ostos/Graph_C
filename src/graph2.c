#include <stdlib.h>
#include <string.h> 
#include <assert.h> 
#include <limits.h>
#include "graph.h"
#include "utils/data_structures.h"

#define INITIAL_SIZE 123
#define RESIZE_FACTOR 2

// UW_Graph functions, ready, set go!
UW_Graph* init_uw_graph(size_t (*hash)(const char* str, size_t size)) {
  UW_Graph* g = (UW_Graph*) malloc(sizeof(UW_Graph));
  g->hash = hash;
  g->adj_matrix = init_hashmap(false, 0, g->hash);
  g->degree = 0;
  g->n_edges = 0;
  g->n_vertex = 0;
  return g;
}

W_Graph* init_w_graph(size_t (*hash)(const char* str, size_t size)) {
  W_Graph* g = (W_Graph*) malloc(sizeof(W_Graph));
  g->hash = hash;
  g->adj_matrix = init_hashmap(false, 0, g->hash);
  g->degree = 0;
  g->n_edges = 0;
  g->n_vertex = 0;
  return g;
}

UW_Graph* complete_graph(size_t (*hash)(const char* str, size_t size), int n) {
  UW_Graph* g = init_uw_graph(hash);
  assert(g != NULL);
  for (int i = 1; i <= n; i++) {
    int length = snprintf(NULL, 0, "%d", i);
    char str[length];
    snprintf(str, length+1, "%d", i);
    add_vertex(g, NULL, str, length);
  }
  for (Element* i = g->adj_matrix->head; i != NULL ; i = i->next) {
    for (Element* j = i->next; j != NULL; j = j->next) {
      add_edge(g, NULL,((Vertex*)i->value)->label, ((Vertex*)i->value)->label_size,
	       ((Vertex*)j->value)->label, ((Vertex*)j->value)->label_size, 0);
    }
  }
  return g;
}

bool add_vertex(UW_Graph* g, W_Graph* g2, const char* label, size_t label_size)
{
  if (g == NULL) goto g_2;
  {
    char* str = malloc(label_size+1);
    memcpy(str, label, label_size+1);
    Vertex v = {.label = str, .label_size = label_size, .degree = 0, .n_edges = 0, .color = 0};
    v.edges = init_hashmap(false, 0, g->hash);
    if (hashmap_put(g->adj_matrix, (const void*) label, label_size, (void*) &v, sizeof(*label) * label_size, sizeof(Vertex))) {
      g->n_vertex++;
      return true;
    }
    return false;
  }
 g_2:
  if (g2 == NULL) {
    printf("Incorrect pointer");
    return false;
  }
  char* str = malloc(label_size+1);
  memcpy(str, label, label_size+1);
  Vertex v = {.label = str, .label_size = label_size, .degree = 0, .n_edges = 0, .color = 0, .dist = INT_MAX};
  v.edges = init_hashmap(false, 0, g2->hash);
  if (hashmap_put(g2->adj_matrix, (const void*) label, label_size, (void*) &v, sizeof(*label) * label_size, sizeof(Vertex))) {
    g2->n_vertex++;
    return true;
  }
  return false;
}

bool add_edge(UW_Graph* g, W_Graph* g2, char* src, size_t size_src, char* dst, size_t size_dst, int dist)
{
  if (g == NULL) goto g_2;
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
    Edge e_1 = {.vertex = (Vertex*) v_1, .length = 0};
    Edge e_2 = {.vertex = (Vertex*) v_2, .length = 0};
    if (hashmap_put(((Vertex*)v_1)->edges, (const void*) dst, size_dst, (void*) &e_2, sizeof(*src) * size_src, sizeof(Edge)) &&
	hashmap_put(((Vertex*)v_2)->edges, (const void*) src, size_src, (void*) &e_1, sizeof(*dst) * size_dst, sizeof(Edge))) {
      return true;
      g->n_edges++;
    }
    return false;
  }
 g_2:
  if (g2 == NULL) {
    printf("Incorrect pointer");
    return false;
  }
  void*  v_1 = hashmap_get(g2->adj_matrix, (const void*) src, size_src);
  assert(v_1 != NULL);
  if (v_1 == NULL) exit(1);
  assert(g2->hash != NULL);
  ((Vertex*)v_1)->edges->hash_func = g2->hash;
  void*  v_2 = hashmap_get(g2->adj_matrix, (const void*) dst, size_dst);
  assert(v_2 != NULL);
  if (v_2 == NULL) exit(1);
  ((Vertex*)v_2)->edges->hash_func = g2->hash;
  Edge e_1 = {.vertex = (Vertex*) v_1, .length = dist};
  Edge e_2 = {.vertex = (Vertex*) v_2, .length = dist};
  if (hashmap_put(((Vertex*)v_1)->edges, (const void*) dst, size_dst, (void*) &e_2, sizeof(*src) * size_src, sizeof(Edge)) &&
      hashmap_put(((Vertex*)v_2)->edges, (const void*) src, size_src, (void*) &e_1, sizeof(*dst) * size_dst, sizeof(Edge))) {
    return true;
    g2->n_edges++;
  }
  return false;
}

void cut_edge(UW_Graph* g, char* src, size_t size_src, char* dst, size_t size_dst)
{
  Vertex* source = hashmap_get(g->adj_matrix, (const void*) src, size_src) != NULL
    ? (Vertex*) hashmap_get(g->adj_matrix, (const void*) src, size_src) 
    : NULL;
  Vertex* dest = hashmap_get(g->adj_matrix, (const void*) dst, size_dst) != NULL
    ? (Vertex*) hashmap_get(g->adj_matrix, (const void*) dst, size_dst) 
    : NULL;
  if (source == NULL || dest == NULL) return;

  Edge* source_edge = hashmap_get(dest->edges, (const void*) src, size_src) != NULL
    ? (Edge*) hashmap_get(dest->edges, (const void*) src, size_src) 
    : NULL;
  Edge* dest_edge = hashmap_get(source->edges, (const void*) dst, size_dst) != NULL
    ? (Edge*) hashmap_get(source->edges, (const void*) dst, size_dst) 
    : NULL;
  if (source_edge == NULL || dest_edge == NULL) return;
  hashmap_delete(source->edges, (const void*) dst, size_dst);
  hashmap_delete(dest->edges, (const void*) src, size_src);
}
//void contract_edge(UW_Graph* g, char* src, char* dst);

ArrayList* bfs(UW_Graph* g, char* src, size_t size_src, char* dst, size_t size_dst)
{
  Queue* Q = init_queue(1);
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

ArrayList* dfs(UW_Graph* g, char* src, size_t size_src, char* dst, size_t size_dst)
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

bool compare(Priority_Queue* Q, void* a_, void* b_) 
{
  if (b_ == NULL) return true;
  Vertex* a = (Vertex*) a_;
  Vertex* b = (Vertex*) b_;
  if (a->dist > b->dist) return true;
  return false;
}

ArrayList* dijsktra(W_Graph* g, char* src, size_t size_src, char* dst, size_t size_dst)
{
  Priority_Queue* Q = init_p_queue(10, &compare);
  assert(Q !=NULL);
  Vertex* source = hashmap_get(g->adj_matrix, (const void*) src, size_src) != NULL
    ? (Vertex*) hashmap_get(g->adj_matrix, (const void*) src, size_src) 
    : NULL;
  Vertex* dest = hashmap_get(g->adj_matrix, (const void*) dst, size_dst) != NULL
    ? (Vertex*) hashmap_get(g->adj_matrix, (const void*) dst, size_dst) 
    : NULL;
  if (source == NULL || dest == NULL) return NULL;
  source->parent = source;
  source->dist = 0;
  p_queue_push(Q, (void*) source);
  while (!p_queue_empty(Q)) {
    Vertex* actual = (Vertex*) p_queue_pop(Q);
    assert(actual != NULL);
    actual->visited = true;
    for (Element* i = actual->edges->head; i != NULL; i = i->next) {
      if (((Edge*)i->value)->vertex->visited == true) continue;
      if (((Edge*)i->value)->vertex->dist > (actual->dist + ((Edge*)i->value)->length)) {
	((Edge*)i->value)->vertex->dist = actual->dist + ((Edge*)i->value)->length;
	((Edge*)i->value)->vertex->parent = actual;
	p_queue_push(Q, ((void*)((Edge*)(i->value))->vertex));
      }
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
  deinit_p_queue(Q);
  return arraylist;
}
//
//void find_independent_sets(UW_Graph* g, char* src, char* dst);
//void minimun_expansion_tree(UW_Graph* g);
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

int chromatic_number(UW_Graph* g, W_Graph* g2) {
  if (g == NULL) goto c_g2;
  {
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
 c_g2: 
  if (g2 == NULL) return -1;
  int chromatic = 0;
  for (Element* i = g2->adj_matrix->head; i != NULL && i->key != NULL; i = i->next) {
    int colors[g2->n_vertex];
    for (size_t l = 0; l < g2->n_vertex; l++) colors[l] = 0;
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
      if (find_valid_number(colors, g2->n_vertex, k)) {
	((Vertex*)i->value)->color = k;
	if (k > chromatic) chromatic = k;
	break;
      }
    }
  }
  return chromatic;
}

void print_graph(UW_Graph* g, W_Graph* g2) {
  if (g == NULL) goto g_2;

  printf("\n");
  for (Element* i = g->adj_matrix->head; i != NULL && i->key != NULL; i = i->next) {
    printf("{");
    printf("{%s}", ((Vertex*)i->value)->label);
    for (Element* j = ((Vertex*)i->value)->edges->head;  j != NULL; j = j->next) {
      printf(" %s", ((Edge*)j->value)->vertex->label);
    }
    printf("}\n");
  }
 g_2:
  if (g2 == NULL) return;
  printf("\n");
  for (Element* i = g2->adj_matrix->head; i != NULL && i->key != NULL; i = i->next) {
    printf("{");
    printf("{%s, %zu}", ((Vertex*)i->value)->label, ((Vertex*)i->value)->dist);
    for (Element* j = ((Vertex*)i->value)->edges->head;  j != NULL; j = j->next) {
      printf(" (%s, %zu)", ((Edge*)j->value)->vertex->label, ((Edge*)j->value)->vertex->dist);
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

void deinit_graph(UW_Graph* g, W_Graph* g2)
{
  if (g == NULL) goto g_2;
  for (Element* i = g->adj_matrix->head; i != NULL ; i = i->next) {
    free(((Vertex*)i->value)->label);
    deinit_hashmap(((Vertex*)i->value)->edges);
  }
  deinit_hashmap(g->adj_matrix);
  free(g);
 g_2:
  if (g2 == NULL) return;
  for (Element* i = g2->adj_matrix->head; i != NULL ; i = i->next) {
    free(((Vertex*)i->value)->label);
    deinit_hashmap(((Vertex*)i->value)->edges);
  }
  deinit_hashmap(g2->adj_matrix);
  free(g);
}
