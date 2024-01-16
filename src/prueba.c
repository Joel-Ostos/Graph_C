#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

size_t hash_a(const char* str, size_t size) {
  int hash = 5381;
  size_t c = 0;
  while (c < size) {
    hash = ((hash << 5) + hash) + str[c]; 
    c++;
  }
  return hash;
}

int main(void) {
  Graph* g = init_graph(*hash_a);
  add_vertex(g, "Colombia", strlen("Colombia"));
  add_vertex(g, "Brasil", strlen("Brasil"));
  add_vertex(g, "Peru", strlen("Peru"));
  add_vertex(g, "Ecuador", strlen("Ecuador"));
  add_vertex(g, "Bolivia", strlen("Bolivia"));
  add_vertex(g, "Chile", strlen("Chile"));

  add_edge(g, "Colombia", strlen("Colombia"), "Brasil", strlen("Brasil"), 0);
  add_edge(g, "Colombia", strlen("Colombia"), "Peru", strlen("Peru"), 0);
  add_edge(g, "Colombia", strlen("Colombia"), "Ecuador", strlen("Ecuador"), 0);
  add_edge(g, "Peru", strlen("Peru"), "Bolivia", strlen("Bolivia"), 0);
  add_edge(g, "Peru", strlen("Peru"), "Ecuador", strlen("Ecuador"), 0);
  add_edge(g, "Peru", strlen("Peru"), "Chile", strlen("Chile"), 0);
  add_edge(g, "Peru", strlen("Peru"), "Brasil", strlen("Brasil"), 0);

  print_graph(g);
  ArrayList* arr = bfs(g, "Colombia", strlen("Colombia"), "Chile", strlen("Chile"));
  if (arr != NULL) {
    print_traversal(arr);
    deinit_traversal(arr);
  }
  ArrayList* arr_2 = dfs(g, "Colombia", strlen("Colombia"), "Chile", strlen("Chile"));
  if (arr_2 != NULL) {
    print_traversal(arr_2);
    deinit_traversal(arr_2);
  }
  print_graph(g);
  printf("Chromatic number graph 2: %d", chromatic_number(g));
  deinit_graph(g);

  Graph* k_3 = init_graph(&hash_a);
  add_vertex(k_3, "1", 1);
  add_vertex(k_3, "2", 1);
  add_vertex(k_3, "3", 1);
  add_vertex(k_3, "4", 1);
  add_vertex(k_3, "5", 1);
  add_vertex(k_3, "6", 1);

  add_edge(k_3, "1", 1, "2", 1, 0);
  add_edge(k_3, "1", 1, "6", 1, 0);
  add_edge(k_3, "1", 1, "3", 1, 0);
  add_edge(k_3, "1", 1, "4", 1, 0);

  add_edge(k_3, "2", 1, "3", 1, 0);
  add_edge(k_3, "3", 1, "4", 1, 0);
  add_edge(k_3, "5", 1, "4", 1, 0);
  add_edge(k_3, "6", 1, "4", 1, 0);
  print_graph(k_3);
  arr = bfs(k_3, "2", 1, "6", 1);
  if (arr != NULL) {
    printf("BFS from 2 to 6: ");
    print_traversal(arr);
    deinit_traversal(arr);
  }
  arr_2 = dfs(k_3, "2", 1, "6", 1);
  if (arr_2 != NULL) {
    printf("DFS from 2 to 6: ");
    print_traversal(arr_2);
    deinit_traversal(arr_2);
  }
  printf("Chromatic number graph 2: %d", chromatic_number(k_3));
  deinit_graph(k_3);

  g = complete_graph(&hash_a, 100);
  print_graph(g);
  deinit_graph(g);
}
