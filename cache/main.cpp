#include <iostream>
#include <string>
#include "cache.h"



int main( void )
{
  int hits = 0, capacity = 0, calls_amount = 0;

  std::cout << "Input maximum capacity of cache:\n";

  std::cin >> capacity;

  std::cout << "Input amount of calls:\n";

  std::cin >> calls_amount;

  LFU_cache<int> lfu(capacity);

  for (int i = 0; i < calls_amount; ++i)
  {
    int request = 0;
    std::cout << "Input request #" << i << "\n";
    std::cin >> request;

    if (lfu.Request(request))
      ++hits;
  }

  std::cout << "Total amounts of hits = " << hits << "\n";
  std::cout << "------------LIST DUMP-----------------------\n";
  std::cout << lfu << "\n";
  return 0;
}
/* TODO:
 * 1. create dummy hash especial for int type (template)
 * 2. add counter to every element
 */

/* TODO:
 * 1. хэшируем данные
 * 2. ищем в мап по ключу
 * если нашли в мап:
 *   ищем в листе
 *   если нашли:
 *     ок (конец программы) (проваливаемся по итератору)
 *   иначе:
 *    если размер общего листа >= максимального:
 *      удаляем наименее используемый (min count)
 *    добавляем в лист + итератор в ветку мапа
 *    конец программы
 *  иначе:
 *    создаём новый листв мапе и кладём итератор на новый элемент
 *    в общем листе (с условием удаления наименьшего)
 */