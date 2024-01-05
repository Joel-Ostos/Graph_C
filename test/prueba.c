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
}
