#include "../src/graph.h"
#include <string.h>

int main(void)
{
  Graph* g = init_graph(false, 0);
  //add_vertex(g, "11", 2);
  //add_vertex(g, "1", 1);
  //add_vertex(g, "2", 1);
  //add_vertex(g, "12", 2);
  //add_vertex(g, "1", 1);
  //add_vertex(g, "13", 2);
  //add_vertex(g, "14", 2);
  //add_vertex(g, "15", 2);
  //add_vertex(g, "16", 2);
  //add_vertex(g, "21", 2);
  //add_vertex(g, "22", 2);
  //add_vertex(g, "23", 2);
  //add_vertex(g, "2", 1);
  //add_vertex(g, "3", 1);
  //add_vertex(g, "24", 2);
  //add_vertex(g, "25", 2);
  //add_vertex(g, "26", 2);

  //add_edge(g, "1", 1, "2", 1);
  //add_edge(g, "1", 1, "3", 1);
  //add_edge(g, "1", 1, "4", 1);

  //add_edge(g, "2", 1, "1", 1);
  //add_edge(g, "12", 2, "1", 1);
  //add_edge(g, "12", 2, "13", 2);
  //add_edge(g, "23", 2, "26", 2);
  //add_edge(g, "2", 1, "3", 1);
  //add_edge(g, "2", 1, "4", 1);

  //add_edge(g, "3", 1, "1", 1);
  //add_edge(g, "3", 1, "2", 1);
  //add_edge(g, "3", 1, "4", 1);

  //add_edge(g, "4", 1, "1", 1);
  //add_edge(g, "4", 1, "2", 1);
  //add_edge(g, "4", 1, "3", 1);

  add_vertex(g, "Colombia", strlen("Colombia"));
  add_vertex(g, "Venezuela", strlen("Venezuela"));
  add_vertex(g, "Ecuador", strlen("Ecuador"));
  add_vertex(g, "Peru", strlen("Peru"));
  add_vertex(g, "Brazil", strlen("Brazil"));

  add_edge(g, "Colombia", strlen("Colombia"), "Venezuela", strlen("Venezuela"));
  //add_edge(g, "Colombia", strlen("Colombia"), "Brazil", strlen("Brazil"));
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
}
