#include <iostream>
#include <vector>
#include <string>
#include <limits>

#define DEBUG 1


class LCS
{
  std::string u;
  std::string v;
  
  std::vector<std::vector<short> > len;

public:
  enum str
  {
    U,
    V
  };
  
  void read_line(str s)
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
  
  void clear()
  {
    u.clear();
    v.clear();
    len.clear();
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

  short d;
  std::cin >> d;
  while(d > 0)
  {
    omg_just_ignore_this_number_and_go_on();
    lcs.read_line(LCS::U);
    
    omg_just_ignore_this_number_and_go_on();
    lcs.read_line(LCS::V);
    
    lcs.DEBUG_print_strings();
    lcs.clear();    
    --d;
  }

  return 0;
}

