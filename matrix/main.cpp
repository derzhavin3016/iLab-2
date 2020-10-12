#include <iostream>
#include <vector>
#include "matrix.hpp"

int main( void )
{
  std::vector<int> v = {0, 1, 1, 0};
  Matrix<int> m1{2, 2, v.begin(), v.end()};

  std::cout << m1;

  return 0;
}
