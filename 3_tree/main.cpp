#include <iostream>
#include "Tree.hpp"
#include <vector>

// the first - the smaller
using veccnt = std::vector<size_t>;



void GetRequests( ad_set::Tree<int> &tr )
{
  size_t req_amount = 0;

  std::cin >> req_amount;

  // first - smaller
  int fst = 0, sec = 0;
  for (size_t i = 0; i < req_amount; ++i)
  {
    std::cin >> fst >> sec;
    if (fst > sec)
      std::swap(fst, sec);

    auto imin = tr.lower_bound(fst);
    if (*imin == fst)
      ++imin;
    auto itend = tr.end();
    size_t count = 0;

    for (auto It = imin; It != itend && *It < sec; ++It, ++count);

    std::cout << count << " ";
  }
  std::cout << "\n";
}

using trint = ad_set::Tree<int>;

int main( void )
{
  trint tr;
  std::cin >> tr;

  GetRequests(tr);
  // FOR DEBUG
  //tr.DotDump("b.png");
  return 0;
}
// TODO:
/*
 * Можно передлать дерево немного для упрощения копирования - хранить сами элементы в массиве (листе)
 * и все указатели указывают на элементы массива, работа с деревом не поменяется, зато копирование и удаление в разы упростится
 *
 */


