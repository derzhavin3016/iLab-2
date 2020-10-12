#ifndef MATRIX_MATRIX_HPP
#define MATRIX_MATRIX_HPP

#include <cmath>

template <typename T>
T Clamp( T val, T min, T max )
{
  return val > max ? max : val < min ? min : val;
}

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
                                                   rows_(rows),
                                                   cols_(cols)
  {
    Alloc();
    size_t i = 0, size = rows_ * cols_;
    for (It it = begin; it != end &&  i < size; ++it, ++i)
      matr_[i / rows_][i % rows_] = *it;
  }

  const T *operator []( size_t i ) const
  {
    return matr_[i >= rows_ ? rows_ - 1 : i];
  }

  ~Matrix( void )
  {
    for (size_t i = 0; i < rows_; ++i)
      delete[] matr_[i];

    delete[] matr_;
    matr_ = nullptr;
  }

  void Dump( std::ostream &ost ) const
  {
    for (size_t i = 0; i < rows_; ++i)
    {
      ost << "|| ";
      for (size_t j = 0; j < rows_; ++j)
        ost << matr_[i][j] << (j == rows_ - 1 ? "" : ", ");
      ost << " ||\n";
    }
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

template <typename T>
std::ostream & operator << ( std::ostream &ost, const Matrix<T> &matr )
{
  matr.Dump(ost);

  return ost;
}

#endif //MATRIX_MATRIX_HPP
