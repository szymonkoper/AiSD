#include <vector>
#include <list>
#include <queue>
#include <cstdio>
#include <stdbool.h>
#include <climits>



struct Node
{
  short id;
  int dist;
  std::list<std::pair<short,int> > edges;
  
  Node(const short i, const int d) : id(i), dist(d)
  { }
};

bool operator> (const Node& a, const Node& b)
{
  return a.dist > b.dist;
}

struct CompareNode
{
	bool operator()(const Node* lhs, const Node* rhs) const
	{
		return *lhs > *rhs;
	}
};



int main()
{
  short cities_number;
  int connections_number;
  scanf("%hd %d", &cities_number, &connections_number);

  std::vector<Node> nodes;
  nodes.resize(cities_number + 1, Node(0, INT_MAX));
  nodes[1].dist = 0;
  
  for (int i = 0; i <= cities_number; ++i)
    nodes[i].id = i;

  for (int i = 1; i <= connections_number; ++i)
  {
    int a, b, w;
    
    scanf("%d %d %d", &a, &b, &w);
    nodes[a].edges.push_back( std::pair<short,int>(b, w) );
    nodes[b].edges.push_back( std::pair<short,int>(a, w) );
  }

  std::priority_queue<Node*, std::vector<Node*>, CompareNode > queue;
  queue.push( &(nodes[1]) );
  
  while (!queue.empty())
  {
    Node* n = queue.top();
    queue.pop();
    
    for (std::list<std::pair<short,int> >::iterator it = n->edges.begin(); it != n->edges.end(); ++it)
    {      
      short to = it->first;
      int weight = it->second;
      
      if (n->dist + weight < nodes[to].dist)
      {
        nodes[to].dist = n->dist + weight;
        queue.push( &(nodes[to]) );
      }  
    }
  }
  
  for (int i = 2; i <= cities_number; ++i)
  {
    printf("%d ", nodes[i].dist);
  }
  printf("\n");
  
  
  return 0;
}








