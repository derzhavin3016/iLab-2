#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "mth.hpp"


size_t Intersect( std::vector<Trian> &trians )
{
  size_t num_of_intr = 0,
         size_tr = trians.size();

  for (size_t i = 0; i < size_tr; ++i)
    for (size_t j = i + 1; j < size_tr; ++j)
      num_of_intr += IsIntersect(trians[i], trians[j]);

  return num_of_intr;
}

int RunTests( std::istream &src )
{
  size_t N = 0;

  src >> N;

  std::vector<Trian> trians(N);

  for (size_t i = 0; i < N; ++i)
    src >> trians[i];

  return Intersect(trians);
}

int main( void )
{
  size_t num_of_intr = 0;
  std::cout << "File - print f, stdin - print s\n";
  char key = 0;
  std::cin >> key;

  std::ifstream fin;
  std::string filename;

  switch (key)
  {
  case 'f':
    std::cout << "Input filename:\n";
    std::cin >> filename;

    fin.open(filename);

    if (!fin.is_open())
    {
      std::cout << "Cannot open file " << filename << "\n";
      return 1;
    }

    num_of_intr = RunTests(fin);
    fin.close();
    break;
  case 's':
    num_of_intr = RunTests(std::cin);
    break;
  default:
    std::cout << "Invalid option: '" << key << "'\n";
    return 1;
  }

  std::cout << "Amount of intersections: " << num_of_intr << "\n";

  return 0;
}
