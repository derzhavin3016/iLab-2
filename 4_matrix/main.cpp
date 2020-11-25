#include <iostream>
#include "matrix.hpp"

int main( void )
{
  ad6::Matrix<ad6::ldbl> m{1, 1};

  ad6::InputQuadr(std::cin, m);
  std::cout << m.Det() << "\n";
  return 0;
}