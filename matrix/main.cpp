#include <iostream>
#include <vector>
#include "matrix.hpp"

int main( void )
{
  std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  //std::cout << *vec.begin();
  ad6::Matrix<int> m{[](int i, int j)-> int {return i > j ? i + j : 0;}, 5, 5},
                  m2{[](int i, int j)-> int {return 27;}, 5, 3};

  std::cin >> m;
  //m1 *= 2;
  //m1.Transpose();
  std::cout << m;

  return 0;
}
