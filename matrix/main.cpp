#include <iostream>
#include <vector>
#include "matrix.hpp"

int main( void )
{
  std::vector<int> vec = {45, 56, 29, 32};
  //std::cout << *vec.begin();
  ad6::Matrix<int> m{2, 2, vec.begin(), vec.end()};


  //m1 *= 2;
  //m1.Transpose();
  std::cout << m << m.Det();
  return 0;
}
