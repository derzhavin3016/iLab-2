#include <iostream>
#include "Tree.hpp"
#include <vector>
#include <set>

#define B std::cout << *(st.begin()) << "\n" << *(--st.end()) << "\n";

using std::vector;
using RQvec = vector<std::pair<int, int>>;

vector<size_t> veckey;
RQvec vecreq;

template <class Tree>
void Test( Tree &tr )
{
  for (auto &elem : veckey)
    tr.insert(elem);

  // first - smaller
  for (auto &elem : vecreq)
  {
    auto imin = tr.lower_bound(elem.first);
    if (*imin == elem.first)
      ++imin;
    auto itend = tr.end();
    size_t count = 0;

    for (auto It = imin; It != itend && *It < elem.second; ++It, ++count);

    std::cout << count << " ";
  }
  std::cout << "\n";
}

int main( void )
{
  size_t keynum = 0, req_amount = 0;
  ad6::Tree<int> tr;
  std::set<int> set;

  std::cin >> keynum;
  veckey.resize(keynum);

  for (auto &elem : veckey)
    std::cin >> elem;

  std::cin >> req_amount;
  vecreq.resize(req_amount);

  for (auto &elem : vecreq)
    std::cin >> elem.first >> elem.second;

  Test(tr);
  Test(set);


  // FOR DEBUG
  //tr.DotDump();
  return 0;
}
