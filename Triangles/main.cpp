#include <iostream>
#include "vec.h"

int main( void )
{
  Vec a(1, 0, 0), b(0, 1, 0);

  std::cout << (a + b);
  return 0;
}