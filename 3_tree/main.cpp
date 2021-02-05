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

  //GetRequests(tr);

  //tr.DotDump("a.png");

  GetRequests(tr);

  //ad6::Tree<int>::iterator It = tr.begin();

  //tr.Erase(*It);

  // FOR DEBUG
  //tr.DotDump("b.png");
  return 0;
}
// TODO:
/*
 * Ok, что бросается в глаза без тестов корректности:

(1) OK

friend class Tree<T>;
friend class Tree_it<T>;

Так себе идея. Лучше занесите Node в namespace detail и сделайте поля открытыми или в приватную часть класса Tree и то же самое.

Иначе сейчас я напишу

struct Foo;
template <> class Tree<Foo> {
  // упс, теперь я тоже ваш друг =)
};

(2) OK

ad6::Node<T>::~Node( void )
{
  right_ = nullptr;
  left_ = nullptr;
  parent_ = nullptr;

Бессмысленные зануления, компилятор их выкинет

(3) OK

if (this == nullptr)
    return this;

Бессмысленная проверка, this == null означает что сломана трансляционная модель

(4) OK

void RecDotPrint( std::ofstream &oft );  <--- const?

(5) OK

: root_(nullptr),
 min_(nullptr),
 max_(nullptr),
 size_(0)

Предпочитайте тривиальную инициализацию в классе

(6)  MB OK

ad6::Tree<T>::Insert

А как тут с безопасностью исключений?
 * */

