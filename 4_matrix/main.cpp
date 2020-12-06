#include <iostream>
#include "matrix.hpp"

int main( void )
{
  linal::Matrix<linal::ldbl> matr{1, 1};

  linal::InputQuadr(std::cin, matr);

  std::cout << matr.Det() << "\n";
  return 0;
}
