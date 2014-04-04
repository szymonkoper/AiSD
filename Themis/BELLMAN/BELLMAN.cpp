#include <cstdio>
#include <stdbool.h>
#include <climits>
#include <vector>
#include <list>


namespace Data
{
  int n, m, s; // #nodes, #edges, start_node_id
  std::vector<std::list<std::pair<int,int> > > edges;

  void read_init()
  {
    scanf("%d %d %d", &n, &m, &s);
    edges.resize(n + 1);
  }

  void read_edges()
  {
    for (int i = 0; i < m; ++i)
    {
      int a, b, c; // edge from a to b with weight c
      scanf("%d %d %d", &a, &b, &c);

      //edges[a].
    }
  }
}

namespace Bellman
{
  void init()
  {
  }

  bool run()
  {
    //for
    return true;
  }
}

int main()
{
  Data::read_init();
  Data::read_edges();

  Bellman::init();

  if (Bellman::run())
    printf("TAK\n"); // TODO
  else
    printf("NIE\n");

  return 0;
}

