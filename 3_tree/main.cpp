#include <iostream>
#include "Tree.hpp"
#include <set>

#define B std::cout << *(st.begin()) << "\n" << *(--st.end()) << "\n";

int main( void )
{
  ad6::Tree<int> tr;
  std::cin >> tr;


  tr.DotDump();
  return 0;
}
