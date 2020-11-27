#include <iostream>
#include "Tree.hpp"
#include <set>

#define B std::cout << *(st.begin()) << "\n" << *(--st.end()) << "\n";

int main( void )
{
  ad6::Tree<int> tr;
  //std::cin >> tr;
  for (int i = 0; i < 100; ++i)
    tr << i;
  //tr << 10 << 12 << 8 << 5 << 9 << 6;



  // for debug
  tr.DotDump();
  return 0;
}
