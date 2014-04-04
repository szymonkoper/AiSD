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

      edges[a].push_back( std::pair<int,int>(b, c) );
    }
  }
}

namespace Bellman
{
  std::vector<long long int> min_paths;
  
  void init()
  {
    min_paths.resize(Data::n + 1, LONG_MAX);
    min_paths[Data::s] = 0;
  }

  void relax(const int u, const int v, const int w)
  {
    if ((min_paths[u] != LONG_MAX) && (min_paths[v] > min_paths[u] + w))
    {
      min_paths[v] = min_paths[u] + w;
    }
  }

  bool run()
  {
    for (int i = 0; i <= Data::n; ++i)
    {
      for (std::list<std::pair<int,int> >::iterator it = Data::edges[i].begin(); it != Data::edges[i].end(); ++it)
      {
        relax(i, it->first, it->second);
      }
    }
    for (int i = 0; i <= Data::n; ++i)
    {
      for (std::list<std::pair<int,int> >::iterator it = Data::edges[i].begin(); it != Data::edges[i].end(); ++it)
      {
        if ((min_paths[i] != LONG_MAX) && (min_paths[it->first] > min_paths[i] + it->second))
        {
          return false;
        }
      }
    }
    return true;
  }
  
  void print_accessible_distances()
  {
    for (int i = 0; i <= Data::n; ++i)
    {
      if ((i != Data::s) && (min_paths[i] != LONG_MAX))
      {
        printf("%d %lld\n", i, min_paths[i]);
      }
    }
  }
  
  void print_cycle()
  {
    printf("NIE\n");
  }
}


int main()
{
  Data::read_init();
  Data::read_edges();

  Bellman::init();

  if (Bellman::run())
    Bellman::print_accessible_distances();
  else
    Bellman::print_cycle();

  return 0;
}

