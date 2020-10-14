#include <iostream>
#include <vector>
#include <cmath>
#include "matrix.hpp"

int main( void )
{
  try
  {
    Matrix<int> m1{4, 4, 5};

    m1 *= 2;
    //m1.Transpose();

    std::cout << m1;
  }
  catch ( const Error &err )
  {
    std::cout << err;
  }
  catch (...)
  {
    std::cout << "Uncaught throw.\n";
  }

  return 0;
}
