#include <iostream>
#include "Tree.hpp"
#include <set>

#define B std::cout << *(st.begin()) << "\n" << *(--st.end()) << "\n";

int main( void )
{
 // std::set<int> st;
  // std::cout << *(st.begin()) << "\n";



  ad6::Tree<int> tr;
  tr << 12 << 13 << 10 << 5 << 6 << 3 << 8 << 1;

  //tr.At(1);
  tr.DotDump();
  return 0;
}
