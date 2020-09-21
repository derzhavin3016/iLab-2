#include <iostream>
#include "mth.hpp"

int main( void )
{
  Trian tr1(Vec(0), Vec(1, 0, 0), Vec(0, 1, 0)),
        tr2(Vec(0, 0, 1), Vec(1, 0, 1), Vec(0, 1, 1));

  std::cout << IsIntersect(tr1, tr2) << "\n";
  return 0;
}
