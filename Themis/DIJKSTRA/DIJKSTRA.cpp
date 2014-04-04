#include <vector>
#include <list>
#include <queue>
#include <cstdio>


#define DEBUG 1


struct Edge
{
  int to;
  int weight;
  
  Edge(const int to, const int weight) : to(to), weight(weight)
  { }
};

namespace Data
{
  int cities_number = 0;
  int connections_number = 0;
  
  std::vector<std::list<Edge> > cities;
  
  void read_all()
  {
    scanf("%d %d", &cities_number, &connections_number);
    
    cities.resize(cities_number + 1);    
    for (int i = 1; i <= connections_number; ++i)
    {
      int a, b, w;
      
      scanf("%d %d %d", &a, &b, &w);
      cities[a].push_back( Edge(b, w) );
      cities[b].push_back( Edge(a, w) );
    }
  }
  
  void DEBUG_print_data()
  {
    if (DEBUG)
    {
      printf("//DEBUG BEGIN:\n");
      printf("cities: %d \tconnections: %d\n", cities_number, connections_number);
      
      for (int i = 1; i <= cities_number; ++i)
      {
        for (std::list<Edge>::iterator it = cities[i].begin(); it != cities[i].end(); ++it)
        {
          printf("Edge from %d\t to %d\t weight\t %d\n", i, (*it).to, (*it).weight);
        }
      }
      printf("//DEBUG END\n");
    }
  }
};

namespace Dijkstra
{
  std::vector<bool> visited_cities;
  std::vector<int> min_paths;
  
  void init_values()
  {
    visited_cities.resize(Data::cities_number + 1);
    min_paths.resize(Data::cities_number + 1);
  }
}


int main()
{
  Data::read_all();
  Data::DEBUG_print_data();
  
  Dijkstra::init_values();
  
  return 0;
}








