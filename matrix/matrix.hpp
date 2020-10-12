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

    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < cols_; ++j)
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
    ~Matrix();
    new(this) Matrix{matr};
    return *this;
  }

  Matrix & operator = ( Matrix &&matr )
  {
    this->~Matrix();
    new(this) Matrix{std::move(matr)};
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

  static Matrix Identity( int rows, int cols )
  {
    Matrix id{rows, cols, 0};
    size_t min_dim = std::min(rows, cols);
    for (size_t i = 0; i < min_dim; ++i)
      id.matr_[i][i] = 1;

    return id;
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
    rows_ = cols_ = 0;
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
