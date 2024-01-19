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
  UW_Graph* g = init_uw_graph(*hash_a);
  add_vertex(g, NULL, "Colombia", strlen("Colombia"));
  add_vertex(g, NULL, "Brasil", strlen("Brasil"));
  add_vertex(g, NULL, "Peru", strlen("Peru"));
  add_vertex(g, NULL, "Ecuador", strlen("Ecuador"));
  add_vertex(g, NULL, "Bolivia", strlen("Bolivia"));
  add_vertex(g, NULL, "Chile", strlen("Chile"));

  add_edge(g, NULL, "Colombia", strlen("Colombia"), "Brasil", strlen("Brasil"), 0);
  add_edge(g, NULL, "Colombia", strlen("Colombia"), "Peru", strlen("Peru"), 0);
  add_edge(g, NULL, "Colombia", strlen("Colombia"), "Ecuador", strlen("Ecuador"), 0);
  add_edge(g, NULL, "Peru", strlen("Peru"), "Bolivia", strlen("Bolivia"), 0);
  add_edge(g, NULL, "Peru", strlen("Peru"), "Ecuador", strlen("Ecuador"), 0);
  add_edge(g, NULL, "Peru", strlen("Peru"), "Chile", strlen("Chile"), 0);
  add_edge(g, NULL, "Peru", strlen("Peru"), "Brasil", strlen("Brasil"), 0);

  print_graph(g, NULL);
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
  print_graph(g, NULL);
  printf("Chromatic number graph 2: %d", chromatic_number(g, NULL));
  deinit_graph(g, NULL);

  UW_Graph* k_3 = init_uw_graph(&hash_a);
  add_vertex(k_3, NULL,"1", 1);
  add_vertex(k_3, NULL,"2", 1);
  add_vertex(k_3, NULL,"3", 1);
  add_vertex(k_3, NULL,"4", 1);
  add_vertex(k_3, NULL,"5", 1);
  add_vertex(k_3, NULL,"6", 1);

  add_edge(k_3, NULL, "1", 1, "2", 1, 0);
  add_edge(k_3, NULL, "1", 1, "6", 1, 0);
  add_edge(k_3, NULL, "1", 1, "3", 1, 0);
  add_edge(k_3, NULL, "1", 1, "4", 1, 0);

  add_edge(k_3, NULL, "2", 1, "3", 1, 0);
  add_edge(k_3, NULL, "3", 1, "4", 1, 0);
  add_edge(k_3, NULL, "5", 1, "4", 1, 0);
  add_edge(k_3, NULL, "6", 1, "4", 1, 0);
  print_graph(k_3, NULL);
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
  printf("Chromatic number graph 2: %d", chromatic_number(k_3, NULL));
  deinit_graph(k_3, NULL);

  g = complete_graph(&hash_a, 100);
  print_graph(g, NULL);
  printf("Chromatic number graph 3: %d", chromatic_number(g, NULL));
  deinit_graph(g, NULL);

  W_Graph* wg = init_w_graph(*hash_a);
  add_vertex(NULL, wg, "1", 1);
  add_vertex(NULL, wg, "2", 1);
  add_vertex(NULL, wg, "3", 1);
  add_vertex(NULL, wg, "4", 1);
  add_vertex(NULL, wg, "5", 1);
  add_edge(NULL, wg, "1", 1, "3", 1, 10);
  add_edge(NULL, wg, "1", 1, "2", 1, 3);
  add_edge(NULL, wg, "4", 1, "2", 1, 20);
  add_edge(NULL, wg, "4", 1, "3", 1, 1);
  add_edge(NULL, wg, "4", 1, "5", 1, 1);
  ArrayList* result = dijsktra(wg, "1", 1, "5", 1);
  print_graph(NULL, wg);
  if (result != NULL) {
    printf("Result Dijsktra Algorithm: ");
    print_traversal(result);
    deinit_traversal(result);
  }
  printf("Chromatic Number Graph 4: %d",chromatic_number(NULL, wg));
  W_Graph* wg_2 = init_w_graph(*hash_a);
  add_vertex(NULL, wg_2, "1", 1);
  add_vertex(NULL, wg_2, "2", 1);
  add_vertex(NULL, wg_2, "3", 1);
  add_vertex(NULL, wg_2, "4", 1);
  add_vertex(NULL, wg_2, "5", 1);
  add_vertex(NULL, wg_2, "6", 1);
  add_vertex(NULL, wg_2, "7", 1);

  add_edge(NULL, wg_2, "1", 1, "2", 1, 1);
  add_edge(NULL, wg_2, "1", 1, "6", 1, 100);
  add_edge(NULL, wg_2, "1", 1, "5", 1, 100);
  add_edge(NULL, wg_2, "1", 1, "7", 1, 100);
  add_edge(NULL, wg_2, "2", 1, "3", 1, 1);
  add_edge(NULL, wg_2, "4", 1, "3", 1, 100);
  add_edge(NULL, wg_2, "3", 1, "5", 1, 1);
  add_edge(NULL, wg_2, "5", 1, "4", 1, 1);
  add_edge(NULL, wg_2, "6", 1, "5", 1, 1);
  add_edge(NULL, wg_2, "6", 1, "7", 1, 1);
  add_edge(NULL, wg_2, "7", 1, "5", 1, 1);

  result = dijsktra(wg_2, "1", 1, "4", 1);
  print_graph(NULL, wg_2);
  if (result != NULL) {
    printf("Result Dijsktra Algorithm: ");
    print_traversal(result);
    deinit_traversal(result);
  }
  printf("Chromatic Number Graph 5: %d",chromatic_number(NULL, wg_2));
}
