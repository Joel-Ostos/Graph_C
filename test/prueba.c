#include "../src/graph.h"
#include <string.h>

int main(void)
{
  Graph* g = init_graph(false, 0);
  Graph* p = init_graph(false, 0);
  for (int i = 0; i < 10; i++) {
    char str[10];
    sprintf(str, "%d", i);
    add_vertex(p, str, strlen(str));
  }
  add_vertex(g, "Colombia", strlen("Colombia"));
  add_vertex(g, "Venezuela", strlen("Venezuela"));
  add_vertex(g, "Ecuador", strlen("Ecuador"));
  add_vertex(g, "Peru", strlen("Peru"));
  add_vertex(g, "Brazil", strlen("Brazil"));

  add_edge(g, "Colombia", strlen("Colombia"), "Venezuela", strlen("Venezuela"), 0);
  add_edge(g, "Colombia", strlen("Colombia"), "Brazil", strlen("Brazil"), 0);
  add_edge(g, "Colombia", strlen("Colombia"), "Peru", strlen("Peru"), 0);
  add_edge(g, "Colombia", strlen("Colombia"), "Ecuador", strlen("Ecuador"), 0);

  add_edge(g, "Peru", strlen("Peru"), "Brazil", strlen("Brazil"), 0);
  add_edge(g, "Peru", strlen("Peru"), "Ecuador", strlen("Ecuador"), 0);

  add_edge(g, "Venezuela", strlen("Venezuela"), "Brazil", strlen("Brazil"), 0);

  print_graph(g);
  traversal* result = bfs(g, "Colombia", strlen("Colombia"), "Brazil", strlen("Brazil"));
  print_traversal_result(result);
  deinit_traversal_result(result);
  deinit_graph(g);
  print_graph(p);
  deinit_graph(p);

  Graph* new = init_graph(false,0);
  add_vertex(new, "1", 1);
  add_vertex(new, "2", 1);
  add_vertex(new, "3", 1);
  add_vertex(new, "4", 1);
  add_vertex(new, "5", 1);
  add_vertex(new, "6", 1);
  add_vertex(new, "7", 1);
  add_vertex(new, "8", 1);
  add_vertex(new, "9", 1);
  add_vertex(new, "10", 2);

  add_edge(new, "1", 1, "2", 1, 0);
  add_edge(new, "2", 1, "1", 1, 0);

  add_edge(new, "2", 1, "3", 1, 0);
  add_edge(new, "3", 1, "2", 1, 0);

  add_edge(new, "3", 1, "4", 1, 0);
  add_edge(new, "4", 1, "3", 1, 0);

  add_edge(new, "4", 1, "5", 1, 0);
  add_edge(new, "5", 1, "4", 1, 0);

  add_edge(new, "5", 1, "1", 1, 0);
  add_edge(new, "1", 1, "5", 1, 0);

  add_edge(new, "5", 1, "10", 2, 0);
  add_edge(new, "10", 2, "5", 1, 0);

  add_edge(new, "1", 1, "6", 1, 0);
  add_edge(new, "6", 1, "1", 1, 0);

  add_edge(new, "2", 1, "7", 1, 0);
  add_edge(new, "7", 1, "2", 1, 0);

  add_edge(new, "3", 1, "8", 1, 0);
  add_edge(new, "8", 1, "3", 1, 0);

  add_edge(new, "4", 1, "9", 1, 0);
  add_edge(new, "9", 1, "4", 1, 0);

  add_edge(new, "10", 2, "7", 1, 0);
  add_edge(new, "7", 1, "10", 2, 0);

  add_edge(new, "10", 2, "8", 1, 0);
  add_edge(new, "8", 1, "10", 2, 0);

  add_edge(new, "6", 1, "9", 1, 0);
  add_edge(new, "9", 1, "6", 1, 0);

  add_edge(new, "6", 2, "8", 1, 0);
  add_edge(new, "8", 1, "6", 2, 0);

  add_edge(new, "7", 1, "9", 1, 0);
  add_edge(new, "9", 1, "7", 1, 0);

  print_graph(new);
  int t = chromatic_number(new);
  printf("\nresult -> %d", t);

  traversal* result_dfs = dfs(new, "1", 1, "10", 2);
  traversal* result_bfs = bfs(new, "1", 1, "10", 2);
  print_traversal_result(result_dfs);
  print_traversal_result(result_bfs);
  deinit_traversal_result(result_dfs);
  deinit_traversal_result(result_bfs);

  deinit_graph(new);
  Graph* k_4 = complete_graph(100);
  print_graph(k_4);
  result_dfs = dfs(k_4, "1", 1, "10", 2);
  result_bfs = bfs(k_4, "1", 1, "10", 2);
  print_traversal_result(result_dfs);
  print_traversal_result(result_bfs);

  deinit_traversal_result(result_dfs);
  deinit_traversal_result(result_bfs);
  int j = chromatic_number(k_4);
  printf("\nresult -> %d", j);
  deinit_graph(k_4);
}
