#include <iostream>
#include <vector>
#include <string>
#include <limits>

#define DEBUG 0


class LCS
{
  std::string u;
  std::string v;
  
  std::vector<std::vector<unsigned short> > lengths;
  
  bool need_predecessors;
  
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
    
    if (need_predecessors)
    {
      directions.resize(u.length() + 1);
      for(std::vector<std::vector<direction> >::iterator it = directions.begin(); it != directions.end(); ++it)
      {
        it->resize(v.length() + 1);
      }
      
      for (unsigned short i = 0; i <= u.length(); ++i)
      {
        directions[i][0] = NONE;
      }
      for (unsigned short i = 1; i <= v.length(); ++i)
      {
        directions[0][i] = NONE;
      }
    }
  }
  
  void set_length_and_path_from_predecessors(const unsigned short col, const unsigned short row)
  {
    const char letter_u = u[col - 1];
    const char letter_v = v[row - 1];

    if (letter_u == letter_v)
    {
      if (need_predecessors) directions[col][row] = DIAGONAL;
      lengths[col][row] = 1 + lengths[col - 1][row - 1];
    }
    else if (lengths[col][row - 1] >= lengths[col - 1][row])
    {
      if (need_predecessors) directions[col][row] = UP;
      lengths[col][row] = lengths[col][row - 1];
    }
    else
    {
      if (need_predecessors) directions[col][row] = LEFT;
      lengths[col][row] = lengths[col - 1][row];
    }
  }

public:
  enum str_id
  {
    U,
    V
  };
  
  void read_line(str_id s)
  {
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
  

  void run(bool predecessors = true)
  {
    need_predecessors = predecessors;
    init();
    
    for (unsigned short row = 1; row <= v.length(); ++row)
    {
      for (unsigned short col = 1; col <= u.length(); ++col)
      {
        set_length_and_path_from_predecessors(col, row);
      }
    }
    
  }
  
  
  unsigned short longest_length()
  {
    return lengths[u.length()][v.length()];
  }
  
  void clear()
  {
    u.clear();
    v.clear();
    lengths.resize(0);
    directions.resize(0);
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
  
  void DEBUG_print_lengths_contents()
  {
    if (DEBUG)
    {
      std::cout << "PRINT LENGTHS CONTENTS:" << std::endl;
      for (unsigned short it_v = 0; it_v <= v.length(); ++it_v)
      {
        for (unsigned short it_u = 0; it_u <= u.length(); ++it_u)
        {
          std::cout << lengths[it_u][it_v] << "\t";
        }
        std::cout << std::endl;
      }
    }
  }

  void DEBUG_print_directions_contents()
  {
    if (DEBUG)
    {
      std::cout << "PRINT DIRECTIONS CONTENTS:" << std::endl;
      for (unsigned short it_v = 0; it_v <= v.length(); ++it_v)
      {
        for (unsigned short it_u = 0; it_u <= u.length(); ++it_u)
        {
          char c = ' ';
          switch(directions[it_u][it_v])
          {
            case NONE:
              c = ' ';
              break;
            
            case UP:
              c = '^';
              break;
            
            case LEFT:
              c = '<';
              break;
            
            case DIAGONAL:
              c = '\\';
              break;
          }
          std::cout << c << "\t";
        }
        std::cout << std::endl;
      }
    }
  }
};


void omg_just_ignore_this_number_and_go_on()
{
  unsigned short x;
  std::cin >> x;
  //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
  std::ios_base::sync_with_stdio(false);

  LCS lcs;

  unsigned short d;
  std::cin >> d;
  while(d > 0)
  {
    lcs.clear();
    
    omg_just_ignore_this_number_and_go_on();
    lcs.read_line(LCS::U);

    omg_just_ignore_this_number_and_go_on();
    lcs.read_line(LCS::V);

    lcs.DEBUG_print_strings();
    
    lcs.run(false);
    std::cout << lcs.longest_length() << std::endl;
    lcs.DEBUG_print_lengths_contents();
    lcs.DEBUG_print_directions_contents();
    
    //lcs.clear();   
    --d;
  }

  return 0;
}

