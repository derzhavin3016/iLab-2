#include <iostream>
#include "Tree.hpp"
#include <vector>

// the first - the smaller
using veccnt = std::vector<size_t>;



void GetRequests( adset::Tree<int> &tr )
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

using trint = adset::Tree<int>;

int main( void )
{
  trint tr;
  std::cin >> tr;

  //tr.DotDump("tr.png");
 /* std::cout << tr.size();

  auto it = tr.begin();

  tr.Erase(it);
  std::cout << tr.size();
*/
  //tr.DotDump("tr1.png");

  //GetRequests(tr);

  //tr.DotDump("a.png");

  //GetRequests(tr);

  //adset::Tree<int>::iterator It = tr.begin();

  //tr.Erase(*It);

  // FOR DEBUG
  //tr.DotDump("b.png");
  return 0;
}
// TODO:
/*
(1) OK

#define B std::cout << *(st.begin()) << "\n" << *(--st.end()) << "\n";

Да ладно? B? Что?

(2)

Сделайте пожалуйста отдельный таргет для тестирования корректности который выводит результаты работы вашего set и один таргет для замеров производительности который запускает там и там но ничего лишнего кроме результата не выводит

Добавьте тестов на десятки тысяч элементов. Сейчас вы в таких тестах будете замерять только вывод на экран по факту, т.к. он у вас не отключаемый

(3) OK

Копирование и присваивание для Tree?

(4) OK

template <typename T>
adset::Tree<T>::Tree( void )
{
}

Во первых явный void в default-ctor не принято писать (ошибкой это не является просто выглядит странно

Во вторых с такой реализацией всё что вам нужно это =default

(5) OK

К слову

namespace adset

Отличное имя неймспейса...

(6) OK

    iterator Find( const T &key );
    iterator Find( const T &key ) const;

Зачем их два?

(7)

Сделайте пожалуйста итеративное удаление
 * */

