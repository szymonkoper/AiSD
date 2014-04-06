#include <iostream>
#include <vector>
#include <string>
#include <limits>

#define DEBUG 1


class LCS
{
  std::string u;
  std::string v;
  
  std::vector<std::vector<unsigned short> > lengths;
  
  enum direction
  {
    NONE,
    UP,
    LEFT,
    DIAGONAL
  };
  
  std::vector<std::vector<direction> > directions;
  
  void init()
  {
    lengths.resize(u.length() + 1);
    
    lengths[0].resize(v.length() + 1, 0);
    
    for(std::vector<std::vector<unsigned short> >::iterator it = lengths.begin() + 1; it != lengths.end(); ++it)
    {
      it->resize(v.length() + 1);
      (*it)[0] = 0;
    }
    
    directions.resize(u.length());
    for(std::vector<std::vector<direction> >::iterator it = directions.begin(); it != directions.end(); ++it)
    {
      it->resize(v.length(), NONE);
    }
  }
  
  unsigned short longest_length_from_predecessors(unsigned short row, unsigned short col)
  {
    char letter_u = u[row + 1];
    char letter_v = v[col + 1];
    
    if (letter_u == letter_v)
    {
      directions[row][col] = DIAGONAL;
      return 1 + lengths[row - 1][col - 1];
    }
    else
    {
      return 0; //TODO
    }
  }

public:
  enum str
  {
    U,
    V
  };
  
  void read_line(str s)
  {
    clear();
    switch (s)
    {
      case U:
        std::cin >> u;
        break;
      
      case V:
        std::cin >> v;
        break;
    }
  }
  

  void run()
  {
    init();
    
    for (unsigned short row = 1; row <= v.length(); ++row)
    {
      for (unsigned short col = 1; col <= u.length(); ++col)
      {
        lengths[row][col] = longest_length_from_predecessors(row, col);
      }
    }
    
  }
  
  int longest_length()
  {
    return lengths[u.length()][v.length()];
  }
  
  void clear()
  {
    u.clear();
    v.clear();
    lengths.clear();
  }
  
  void DEBUG_print_strings()
  {
    if (DEBUG)
    {
      std::cout << "PRINTING STRINGS" << std::endl
                << "U.len=" << u.length() << " with " << u << std::endl
                << "V.len=" << v.length() << " with " << v << std::endl;
    }
  }
};


void omg_just_ignore_this_number_and_go_on()
{
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
  std::ios_base::sync_with_stdio(false);

  LCS lcs;

  unsigned short d;
  std::cin >> d;
  while(d > 0)
  {
    omg_just_ignore_this_number_and_go_on();
    lcs.read_line(LCS::U);

    omg_just_ignore_this_number_and_go_on();
    lcs.read_line(LCS::V);

    lcs.DEBUG_print_strings();
    
    lcs.run();
    std::cout << lcs.longest_length() << std::endl;
    
    //lcs.clear();   
    --d;
  }

  return 0;
}

