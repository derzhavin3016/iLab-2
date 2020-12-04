#include <iostream>
#include "Tree.hpp"
#include <vector>

#define B std::cout << *(st.begin()) << "\n" << *(--st.end()) << "\n";

// the first - the smaller
using veccnt = std::vector<size_t>;



void GetRequests( ad6::Tree<int> &tr )
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

int main( void )
{
  ad6::Tree<int> tr;
  std::cin >> tr;

  GetRequests(tr);

  // FOR DEBUG
  //tr.DotDump();
  return 0;
}

