#include <iostream>
#include <vector>
#include <cmath>
#include "matrix.hpp"

int main( void )
{
 std::vector<int> vec = {1, 0, 0, 1};
 Matrix<int> m{1, 4, vec.begin(), vec.end()};

  //m1 *= 2;
  //m1.Transpose();

  std::cout << m;

  return 0;
}
