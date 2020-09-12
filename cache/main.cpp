#include <iostream>
#include "cache.h"


int main( void )
{
  std::unordered_map<int, std::list<int>> map;



  map[2].push_back(228);

  std::cout << map[2];
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