#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../../matrix.hpp"

using namespace ad6;

template <typename T>
void RawPrint( const Matrix<T> &matr )
{
  int cols = matr.getCols();
  int rows = matr.getRows();

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
      std::cout << matr[i][j] << " ";
    std::cout << "\n";
  }
}


int main( int argc, char *argv[] )
{
  if (argc != 3)
  {
    std::cout << "USAGE: ./gen SIZE DET\n";
    return 0;
  }

  int size = atoi(argv[1]);
  ldbl det = atof(argv[2]);

  Matrix<ldbl> mat{Matrix<ldbl>::Identity(size)};

  mat[0][0] = det;

  srand(clock());


  int end = size * 10;

  for (int i = 0; i < end; ++i)
  {
    srand(clock());
    int sign = rand() % 2 == 1 ? -1 : 1;

    ldbl mult = rand() % 10 + 1;
    ldbl div = rand() % 10 + 1;

    size_t row1 = rand() % size;
    size_t row2 = rand() % size;

    while (row1 == row2)
    {
      srand(clock());
      row1 = rand() % size;
    }

    mat.AddLineMVal(row1, row2, sign * mult / div);
  }


  std::cout << size << "\n";

  RawPrint(mat);
  return 0;
}

