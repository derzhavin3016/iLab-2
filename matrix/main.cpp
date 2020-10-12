#include <iostream>
#include <vector>
#include <cmath>
#include "matrix.hpp"

int main( void )
{
  std::vector<int> v = {0, 10, 1, 0};
  Matrix<int> m1{2, 2, v.begin(), v.end()};

  m1 = Matrix<int>::Identity(4, 4);
  std::cout << m1;

  return 0;
}
