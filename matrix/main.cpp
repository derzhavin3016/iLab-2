#include <iostream>
#include <vector>
#include "matrix.hpp"

int main( void )
{
 std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 //std::cout << *vec.begin();
 ad6::Matrix<int> m{5, 3, vec.begin(), vec.end()};

  //m1 *= 2;
  //m1.Transpose();

  std::cout << m;

  return 0;
}
