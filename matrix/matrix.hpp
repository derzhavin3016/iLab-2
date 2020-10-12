#ifndef MATRIX_MATRIX_HPP
#define MATRIX_MATRIX_HPP

#include <cmath>

template <typename T>
class Matrix
{
private:
  T** matr_;
  size_t rows_, cols_;
public:

  Matrix( int cols, int rows, T val = T{} ) : matr_(nullptr),
                                              rows_(rows),
                                              cols_(cols)
  {
    Alloc();
    Fill(val);
  }

  template <typename It>
  Matrix( int cols, int rows, It begin, It end ) : matr_(nullptr),
                                                   cols_(cols),
                                                   rows_(rows)
  {
    Alloc();
    for (It it = begin; it != end; ++it)

  }

  ~Matrix( void )
  {
    for (size_t i = 0; i < rows_; ++i)
      delete[] matr_[i];

    delete[] matr_;
    matr_ = nullptr;
  }

private:
  void Fill( T val )
  {
    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        matr_[i][j] = val;
  }

  void Alloc( void )
  {
    matr_ = new T*[rows_];

    for (size_t i = 0; i < rows_; ++i)
      matr_[i] = new T[cols_];
  }
};



#endif //MATRIX_MATRIX_HPP
