#include <cstdio>
#include <vector>


namespace Data
{
  short n; // # of rows
  short m; // # of cols
  
  std::vector<std::vector<int> > t;
  
  void init_table()
  {
    t.resize(n);
    for (std::vector<std::vector<int> >::iterator it = t.begin(); it != t.end(); ++it)
    {
      it->resize(m);
    }
  }
  
  void read_size()
  {
    short* rows = &n;
    short* cols = &m;
    scanf("%hd %hd", rows, cols);

  }

  void read_table()
  {
    int val;    

    for (short x = 0; x < n; ++x)
    {
      for (short y = 0; y < m; ++y)
      {
        scanf("%d", &val);
        t[x][y] = val;      
      }
    }
  }
  
  namespace Debug
  {
    void print_table()
    {
      for (int x = 0; x < n; ++x)
      {
        for (int y = 0; y < m; ++y)
        {
          printf("%d ", t[x][y]);
        }
        printf("\n");
      }
    }
  }
}


int main()
{
  Data::read_size();
  Data::init_table();
  Data::read_table();
 
  Data::Debug::print_table(); 
  return 0;
}
