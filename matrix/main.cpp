#include <iostream>
#include <vector>
#include <cmath>
#include "matrix.hpp"

int main( void )
{
  Matrix<int> m1{4, 4, 5};

  m1 *= 2;
  //m1.Transpose();

  std::cout << m1[1][0];

  return 0;
}
