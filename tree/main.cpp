#include <iostream>
#include "Tree.hpp"

int main( void )
{
  ad6::Tree<int> tr;
  tr << 12 << 13 << 10 << 5;

  tr.Erase(13);
  if (!tr.Empty())
    tr.Clear();
  return 0;
}

