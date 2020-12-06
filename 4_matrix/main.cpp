#include <iostream>
#include "matrix.hpp"

using matr = linal::Matrix<linal::ldbl>;

int main( void )
{
  linal::Matrix<linal::ldbl> m1(5, 5, [](int i, int j) {return 5 * i + j; });
  linal::Matrix<linal::ldbl> m2 = m1;

  matr m3 = m2 * 2.0l;

  //linal::InputQuadr(std::cin, m);

  std::cout << m3.Det() << " = " << m1 << " + " << m2 << "\n";
  return 0;
}
