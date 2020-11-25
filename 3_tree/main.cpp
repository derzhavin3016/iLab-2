#include <iostream>
#include "Tree.hpp"
#include <set>

#define B std::cout << *(st.begin()) << "\n" << *(--st.end()) << "\n";

int main( void )
{
  std::set<int> st;
  std::cout << *(st.begin()) << "\n";



  ad6::Tree<int> tr;
  tr << 12 << 13 << 10 << 5;

  tr.At(2);
  return 0;
}
