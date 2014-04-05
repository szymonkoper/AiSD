#include <cstdio>
#include <vector>
#include <climits>


namespace Data
{
  short n; // # of rows
  short m; // # of cols
  
  std::vector<std::vector<int> > weights;
  
  void init_table()
  {
    weights.resize(m);
    for (std::vector<std::vector<int> >::iterator it = weights.begin(); it != weights.end(); ++it)
    {
      it->resize(n);
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

    for (short row = 0; row < n; ++row)
    {
      for (short col = 0; col < m; ++col)
      {
        scanf("%d", &val);
        weights[col][row] = val;
      }
    }
  }
}


namespace Solution
{
  short n;
  short m;
  
  std::vector<std::vector<int> > min_paths;
  
  enum tables
  {
    WEIGHT, PATH
  };
  
  enum directions
  {
    THIS, LEFT_UP, LEFT, LEFT_DOWN, UP, DOWN
  };
  
  int get(tables table, short col, short row, directions direction)
  {
    std::vector<std::vector<int> >* v;
    switch(table)
    {
      case WEIGHT:
        v = &(Data::weights);
        break;
      
      default: //case SOLUTION:
        v = &(Solution::min_paths);
        break;
    }
    
    switch(direction)
    {
      case THIS:
        return (*v)[col][row];
        break;
      case LEFT_UP:
        return (*v)[col-1][row-1];
        break;
      
      case LEFT:
        return (*v)[col-1][row];
        break;
      
      case LEFT_DOWN:
        return (*v)[col-1][row+1];
        break;
      
      case UP:
        return (*v)[col][row-1];
        break;
      
      default: //case DOWN:
        return (*v)[col][row+1];
        break;
    }
  }
  
  void init_table()
  {
    n = Data::n;
    m = Data::m;

    min_paths.resize(m);
    for (std::vector<std::vector<int> >::iterator it = min_paths.begin(); it != min_paths.end(); ++it)
    {
      it->resize(n);
    }
  }
  
  int min(int a, int b)
  {
    if (a <= b) return a;
    else return b;
  }
  
  int min(int a, int b, int c)
  {
    return min(min(a, b), c);
  }

  void check_up_and_down(short col)
  {
    for (short row = 1; row < n; ++row)
    {
      min_paths[col][row] = min(get(PATH,col,row,THIS), get(PATH,col,row,UP) + get(WEIGHT,col,row,THIS));
    }
    for (short row = n - 2; row >= 0; --row)
    {
      min_paths[col][row] = min(get(PATH,col,row,THIS), get(PATH,col,row,DOWN) + get(WEIGHT,col,row,THIS));
    }
  }
  
  int get_best_left(short col, short row)
  {
    int current_weight = get(WEIGHT,col,row,THIS);
    int left_best = min(get(PATH,col,row,LEFT_UP), get(PATH,col,row,LEFT), get(PATH,col,row,LEFT_DOWN));
    return current_weight + left_best;
  }
  
  void check_left(short col)
  {
    min_paths[col][0] = get(WEIGHT,col,0,THIS) + min(get(PATH,col,0,LEFT), get(PATH,col,0,LEFT_DOWN));
    for (short row = 1; row < n - 1; ++row)
    {
      min_paths[col][row] = get_best_left(col, row);
    }
    min_paths[col][n-1] = get(WEIGHT,col,n-1,THIS) + min(get(PATH,col,n-1,LEFT), get(PATH,col,n-1,LEFT_UP));
  }
  
  void run()
  {
    for (short row = 0; row < n; ++ row)
    {
      min_paths[0][row] = Data::weights[0][row];
    }
    for (short col = 1; col < m; ++col)
    {
      check_left(col);
      check_up_and_down(col);
    }   
  }

  int min_path()
  {
    int min = INT_MAX;

    for (short y = 0; y < n; ++y)
    {
      int val = min_paths[m - 1][y];
      if (val < min) min = val;
    }

    return min;
  }
}

int main()
{
  Data::read_size();
  Data::init_table();
  Data::read_table();
  
  Solution::init_table();
  Solution::run();
  printf("%d\n", Solution::min_path());
  
  return 0;
}

