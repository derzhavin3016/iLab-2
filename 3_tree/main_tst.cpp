#include <iostream>
#include <chrono>
#include "Tree.hpp"
#include <vector>
#include <set>

using std::vector;
using RQvec = vector<std::pair<int, int>>;

vector<size_t> veckey;
RQvec vecreq;

bool IsQuiet = false;

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
  }
}

int main( void )
{
  size_t keynum = 0, req_amount = 0;
  ad_set::Tree<int> tr;
  std::set<int> set;

  std::cin >> keynum;
  veckey.resize(keynum);

  for (auto &elem : veckey)
    std::cin >> elem;

  std::cin >> req_amount;
  vecreq.resize(req_amount);

  for (auto &elem : vecreq)
    std::cin >> elem.first >> elem.second;

  auto tr_t1 = std::chrono::high_resolution_clock::now();
  Test(tr);
  auto tr_t2 = std::chrono::high_resolution_clock::now();

  auto set_t1 = std::chrono::high_resolution_clock::now();
  Test(set);
  auto set_t2 = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> tr_dt = tr_t2 - tr_t1, set_dt = set_t2 - set_t1;

  std::cout << "std::set time = " << set_dt.count() << " ms\n";
  std::cout << "Tree time = " << tr_dt.count() << " ms\n";

  // FOR DEBUG
  //tr.DotDump();
  return 0;
}
