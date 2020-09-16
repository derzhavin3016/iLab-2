#include "cache.h"

int GetTestsFromFile( const std::string &filename, std::vector<int> &tests );

int main( int argc, char *argv[] )
{
  std::vector<int> requests;

  std::string filename;
  if (argc == 1)
  {
    std::cout << "Input name of a file with test\n(FORMAT: capacity calls_amount data...)\n";
    std::cin >> filename;
  }
  else
    filename = argv[1];

  int capacity = GetTestsFromFile(filename, requests);
  if (capacity == 0)
    return 1;

  LFU_cache<int> LFU(capacity);

  std::cout << "Hits: " << LFU.Test(requests) << "\n";
  std::cout << "-------------LIST DUMP---------------------\n";
  std::cout << LFU << "\n";



  return 0;
}

int GetTestsFromFile( const std::string &filename, std::vector<int> &tests )
{
  std::ifstream test_file(filename);

  if (!test_file.is_open())
  {
    std::cout << "Error with opening file " << filename << "\n";
    return 0;
  }

  int capacity = 0, calls_amount = 0;
  test_file >> capacity >> calls_amount;

  tests.resize(calls_amount);

  for (int i = 0; i < calls_amount; ++i)
    test_file >> tests[i];

  test_file.close();

  return capacity;
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