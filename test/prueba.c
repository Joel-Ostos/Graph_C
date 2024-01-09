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

  add_edge(g, "Colombia", strlen("Colombia"), "Venezuela", strlen("Venezuela"));
  add_edge(g, "Colombia", strlen("Colombia"), "Brazil", strlen("Brazil"));
  add_edge(g, "Colombia", strlen("Colombia"), "Peru", strlen("Peru"));
  add_edge(g, "Colombia", strlen("Colombia"), "Ecuador", strlen("Ecuador"));

  add_edge(g, "Peru", strlen("Peru"), "Brazil", strlen("Brazil"));
  add_edge(g, "Peru", strlen("Peru"), "Ecuador", strlen("Ecuador"));

  add_edge(g, "Venezuela", strlen("Venezuela"), "Brazil", strlen("Brazil"));

  print_graph(g);
  traversal* result = bfs(g, "Colombia", strlen("Colombia"), "Brazil", strlen("Brazil"));
  print_bfs_result(result);
  deinit_bfs_result(result);
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

  add_edge(new, "1", 1, "2", 1);
  add_edge(new, "2", 1, "1", 1);

  add_edge(new, "2", 1, "3", 1);
  add_edge(new, "3", 1, "2", 1);

  add_edge(new, "3", 1, "4", 1);
  add_edge(new, "4", 1, "3", 1);

  add_edge(new, "4", 1, "5", 1);
  add_edge(new, "5", 1, "4", 1);

  add_edge(new, "5", 1, "1", 1);
  add_edge(new, "1", 1, "5", 1);

  add_edge(new, "5", 1, "10", 2);
  add_edge(new, "10", 2, "5", 1);

  add_edge(new, "1", 1, "6", 1);
  add_edge(new, "6", 1, "1", 1);

  add_edge(new, "2", 1, "7", 1);
  add_edge(new, "7", 1, "2", 1);

  add_edge(new, "3", 1, "8", 1);
  add_edge(new, "8", 1, "3", 1);

  add_edge(new, "4", 1, "9", 1);
  add_edge(new, "9", 1, "4", 1);

  add_edge(new, "10", 2, "7", 1);
  add_edge(new, "7", 1, "10", 2);

  add_edge(new, "10", 2, "8", 1);
  add_edge(new, "8", 1, "10", 2);

  add_edge(new, "6", 1, "9", 1);
  add_edge(new, "9", 1, "6", 1);

  add_edge(new, "6", 2, "8", 1);
  add_edge(new, "8", 1, "6", 2);

  add_edge(new, "7", 1, "9", 1);
  add_edge(new, "9", 1, "7", 1);

  print_graph(new);
  int t = chromatic_number(new);
  printf("\nresult -> %d", t);
  deinit_graph(new);
}
