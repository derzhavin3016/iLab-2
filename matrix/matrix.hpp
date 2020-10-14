#ifndef MATRIX_MATRIX_HPP
#define MATRIX_MATRIX_HPP

#include <cmath>
#include "errors.hpp"

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

  Matrix( int rows, int cols, T val = T{} ) : matr_(nullptr),
                                              rows_(rows),
                                              cols_(cols)
  {
    Alloc();
    Fill(val);
  }

  Matrix( const Matrix &matr ) : matr_(nullptr),
                                 rows_(matr.rows_),
                                 cols_(matr.cols_)
  {
    Alloc();

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        matr_[i][j] = matr[i][j];
  }

  Matrix( Matrix &&matr ) : matr_(matr.matr_),
                            rows_(matr.rows_),
                            cols_(matr.cols_)
  {
    matr.matr_ = nullptr;
    matr.rows_ = 0;
  }

  Matrix & operator = ( const Matrix &matr )
  {
    if (this == &matr)
      return *this;

    Matrix tmp(matr);
    Swap(*this, tmp);

    return *this;
  }

  Matrix & operator = ( Matrix &&matr )
  {
    if (this == &matr)
      return *this;

    Matrix tmp(std::move(matr));
    Swap(*this, tmp);

    return *this;
  }

  template <typename It>
  Matrix( int rows, int cols, It begin, It end ) : matr_(nullptr),
                                                   rows_(rows),
                                                   cols_(cols)
  {
    Alloc();
    size_t i = 0, size = rows_ * cols_;
    for (It it = begin; it != end &&  i < size; ++it, ++i)
      matr_[i / rows_][i % rows_] = *it;
  }

  Matrix & operator += ( const Matrix &matr )
  {
    ASSERT(matr.rows_ == rows_ && matr.cols_ == cols_,
           "Matrix' dimensions are different.");

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        matr_[i][j] += matr.matr_[i][j];

    return *this;
  }

  Matrix & operator -= ( const Matrix &matr )
  {
    ASSERT(matr.rows_ == rows_ && matr.cols_ == cols_,
           "Matrix' dimensions are different.");

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        matr_[i][j] -= matr.matr_[i][j];

    return *this;
  }

  template <typename tpe>
  Matrix & operator *= ( tpe val )
  {
    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        matr_[i][j] *= val;

    return *this;
  }

  Matrix & Transpose( void )
  {
    if (rows_ == cols_)
      return Transpose_Quad();
    return *this;
  }

  size_t getCols( void ) const
  {
    return cols_;
  }

  size_t getRows( void ) const
  {
    return rows_;
  }

  static Matrix Identity( int rows, int cols )
  {
    Matrix id(rows, cols, 0);
    size_t min_dim = std::min(rows, cols);

    for (size_t i = 0; i < min_dim; ++i)
      id.matr_[i][i] = 1;

    return id;
  }

  const T & GetElem( int i, int j ) const
  {
    int new_i = Clamp(i, 0, static_cast<int>(rows_ - 1)),
        new_j = Clamp(j, 0, static_cast<int>(cols_ - 1));

    return matr_[new_i][new_j];
  }

  const T *operator []( int i ) const
  {
    return matr_[Clamp(i, 0, static_cast<int>(rows_ - 1))];
  }

  ~Matrix( void )
  {
    for (size_t i = 0; i < rows_; ++i)
      delete[] matr_[i];

    delete[] matr_;
    matr_ = nullptr;
    rows_ = cols_ = 0;
  }

  void Dump( std::ostream &ost ) const
  {
    for (size_t i = 0; i < rows_; ++i)
    {
      ost << "|| ";
      for (size_t j = 0; j < rows_; ++j)
        ost << matr_[i][j] << (j == rows_ - 1 ? "" : ", ");
      ost << " ||\n ";
    }
  }

private:
  void Fill( T val )
  {
    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        matr_[i][j] = val;
  }

  Matrix & Transpose_Quad( void )
  {
    for (size_t i = 0; i < cols_; ++i)
      for (size_t j = i + 1; j < cols_; ++j)
        std::swap(matr_[i][j], matr_[j][i]);

    return *this;
  }

  void Alloc( void )
  {
    matr_ = new T*[rows_];

    for (size_t i = 0; i < rows_; ++i)
      matr_[i] = new T[cols_];
  }

  static void Swap( Matrix &lhs, Matrix &rhs )
  {
    std::swap(lhs.matr_, rhs.matr_);
    std::swap(lhs.cols_, rhs.cols_);
    std::swap(lhs.rows_, rhs.rows_);
  }

};


template <typename T>
std::ostream & operator << ( std::ostream &ost, const Matrix<T> &matr )
{
  matr.Dump(ost);

  return ost;
}

#endif //MATRIX_MATRIX_HPP
