#include <iostream>
#include "Tree.hpp"
#include <set>

#define B std::cout << *(st.begin()) << "\n" << *(--st.end()) << "\n";

int main( void )
{
  std::set<int> st{5, 6, 4, 2, 1};
  std::cout << *(++st.end()) << "\n";



  ad6::Tree<int> tr;
  tr << 12 << 13 << 10 << 5;

  tr.Erase(13);
  if (!tr.Empty())
    tr.Clear();
  return 0;
}

