#include <iostream>
#include "Tree.hpp"
#include <vector>

#define B std::cout << *(st.begin()) << "\n" << *(--st.end()) << "\n";

// the first - the smaller
using veccnt = std::vector<size_t>;

void GetRequests( ad6::Tree<int> &tr, veccnt &vec )
{
  size_t req_amount = 0;

  std::cin >> req_amount;
  vec.resize(req_amount);

  // first - smaller
  int fst = 0, sec = 0;
  for (size_t i = 0; i < req_amount; ++i)
  {
    std::cin >> fst >> sec;
    if (fst > sec)
      std::swap(fst, sec);

    vec[i] = tr.FindAm(fst, sec);
  }
}

int main( void )
{
  ad6::Tree<int> tr;
  std::cin >> tr;
  veccnt vec;

  GetRequests(tr, vec);

  for (auto &elem : vec)
    std::cout << elem << " ";
  std::cout << "\n";


  // FOR DEBUG
  //tr.DotDump();
  return 0;
}
