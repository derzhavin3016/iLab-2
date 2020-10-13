#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "mth.hpp"


void Intersect( std::vector<Trian> &trians )
{
  size_t size_tr = trians.size();
  size_t cnt = 0;


  bool IsIPrint = false;

  for (size_t i = 0; i < size_tr; ++i)
  {
    IsIPrint = false;
    for (size_t j = i + 1; j < size_tr; ++j)
      if (IsIntersect(trians[i], trians[j]))
      {
        std::cout << j << "\n";
        cnt++;
        IsIPrint = true;
      }
    if (IsIPrint)
      std::cout << i << "\n";
  }

  std::cout << "intersections: " << cnt << "\n";
}

void RunTests( std::istream &src )
{
  size_t N = 0;

  src >> N;

  std::vector<Trian> trians(N);

  for (size_t i = 0; i < N; ++i)
    src >> trians[i];

  Intersect(trians);
}

int main( void )
{
  RunTests(std::cin);
  return 0;
}
