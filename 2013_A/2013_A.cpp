// AiSD 2013_A
// Szymon Koper

#include <stdio.h>
#include <queue>

using namespace std;


unsigned char graph[2000][2000];

struct vertex
{
  unsigned short x;
  unsigned short y;
  unsigned int dist;

  vertex() : x(0), y(0), dist(0) {}
  vertex(unsigned short x, unsigned short y, unsigned int dist) : x(x), y(y), dist(dist) {}

};

int main()
{
  unsigned short x, y; // Graph size: breadth, height
  register unsigned short xx, yy; // Iterators for graph table

  unsigned short Px = 65535;
  unsigned short Py = 65535;

  scanf("%hu %hu", &x, &y);

  // Filling array with lines from input and looking for P
  for (yy = 0; yy < y; yy++)
  {
    scanf("%s", &graph[yy][0]);
    for (xx = 0; xx < x; xx++)
    {
      if (graph[yy][xx] == 'P')
      {
        Px = xx;
        Py = yy;
      }
    }
  }

  x--;
  y--;

  queue <vertex> Q;
  vertex u;

  Q.push(vertex(Px, Py, 0)); // It's the starting P point

  while( !Q.empty() ) // Check all routes for S point (BFS)
  {
    u = Q.front();
    Q.pop();


    // Left vertex
    if (u.x > 0)
    {
      switch (graph[u.y][u.x - 1])
      {
        case '.':
          graph[u.y][u.x - 1] = 'x';
          Q.push(vertex(u.x - 1, u.y, u.dist + 1));
          break;
        case 'S':
          printf("%u\n", u.dist + 1);
          return 0;
      }
    }


    // Right vertex
    if (u.x < x)
    {
      switch (graph[u.y][u.x + 1])
      {
        case '.':
          graph[u.y][u.x + 1] = 'x';
          Q.push(vertex(u.x + 1, u.y, u.dist + 1));
          break;
        case 'S':
          printf("%u\n", u.dist + 1);
          return 0;
      }
    }

    // Top vertex
    if (u.y > 0)
    {
      switch (graph[u.y - 1][u.x])
      {
        case '.':
          graph[u.y - 1][u.x] = 'x';
          Q.push(vertex(u.x, u.y - 1, u.dist + 1));
          break;
        case 'S':
          printf("%u\n", u.dist + 1);
          return 0;
      }
    }

    // Bottom vertex
    if (u.y < y)
    {
      switch (graph[u.y + 1][u.x])
      {
        case '.':
          graph[u.y + 1][u.x] = 'x';
          Q.push(vertex(u.x, u.y + 1, u.dist + 1));
          break;
        case 'S':
          printf("%u\n", u.dist + 1);
          return 0;
      }
    }

   }

  printf("NIE\n");
  return 0;
}
