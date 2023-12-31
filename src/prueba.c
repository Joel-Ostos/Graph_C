#include "graph.h"

int main(void)
{
  Graph* g = init_graph(false, 0);
  add_vertex(g, "1", 1);
  add_vertex(g, "2", 1);
  add_edge(g, "1", 1, "2", 1);
  add_edge(g, "2", 1, "1", 1);
  add_edge(g, "2", 1, "1", 1);
  print_graph(g);
  deinit_graph(g);
}
