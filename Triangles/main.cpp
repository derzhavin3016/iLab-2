#include <iostream>
#include "line.hpp"

int main( void )
{
  Vec a(0), b(5);
  Vec c((a - b).Normalize());
  std::cout << c;
  return 0;
}
