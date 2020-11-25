#ifndef MATRIX_MATRIX_HPP
#define MATRIX_MATRIX_HPP

#include <iostream>
#include <cmath>
#include <assert.h>

template <typename T>
T Clamp( T val, T min, T max )
{
  return val > max ? max : val < min ? min : val;
}



namespace ad6
{
  using ldbl = long double;

  const ldbl MAT_THRESHOLD = 1e-10;
  template <typename T>
  class Matrix
  {
  private:
    T **matr_;
    size_t rows_, cols_;
    static ldbl threshold;
    // emplace function type
    //using empl_func = T (*)( int, int );

    struct Row_matr
    {
      size_t m_cols;
      T *m_row;

      Row_matr( size_t cols, T *row ) : m_cols(cols),
                                        m_row(row)
      {}

      const T &operator []( int i ) const
      {
        return m_row[Clamp(i, 0, static_cast<int>(m_cols - 1))];
      }

      T &operator []( int i )
      {
        return m_row[Clamp(i, 0, static_cast<int>(m_cols - 1))];
      }

      Row_matr( const Row_matr &row_m ) = default;

      Row_matr &operator =( const Row_matr &row_m ) = default;
    };

  public:

    Matrix( int rows, int cols );

    template <typename It>
    Matrix( int rows, int cols, const It &begin, const It &end );

    template <typename empl_func>
    Matrix( int rows, int cols, empl_func fnc );

    // copy constructors
    Matrix( const Matrix &matr );
    // move
    Matrix( Matrix &&matr );

    // assignments opearators
    Matrix &operator =( const Matrix &matr );
    // move
    Matrix &operator =( Matrix &&matr );

    Matrix &operator +=( const Matrix &matr );
    Matrix &operator -=( const Matrix &matr );
    Matrix &operator *=( T val );

    Matrix &Transpose( void );

    Matrix Transposing( void ) const;

    ldbl Det( void ) const;

    size_t getCols( void ) const { return cols_; }
    size_t getRows( void ) const { return rows_; }

    static Matrix Identity( int rows );

    const T &At( int i, int j ) const;

    Row_matr operator []( int i ) const
    {
      return Row_matr{cols_, matr_[Clamp(i, 0, static_cast<int>(rows_ - 1))]};
    }

    Row_matr operator []( int i )
    {
      return Row_matr{cols_, matr_[Clamp(i, 0, static_cast<int>(rows_ - 1))]};
    }

    ~Matrix( void );

    void Dump( std::ostream &ost ) const;

    void AddLineMVal( int dest_ind, int src_ind, ldbl val );

    static void SetThreshold( ldbl new_thres ) { threshold = new_thres; }
    static void SetDefThres ( void )           { threshold = MAT_THRESHOLD; }
    static ldbl GetThreshold( void )           { return threshold; }

  private:
    void Fill( T val );

    Matrix &Transpose_Quad( void );

    void Alloc( void );

    static void Swap( Matrix &lhs, Matrix &rhs );

    /* copy matrix with idnetical sizes function */
    static void Copy( Matrix &dst, const Matrix &src );

    void SwapLines( int lhs, int rhs );

    void AddLine( int dest_ind, int src_ind );

    void MulLine( int line, ldbl val );

    int FindNonZero( int st_col );

    template <typename walk_func>
    void Walker( walk_func walk );
  };

  template <typename T>
  Matrix<T> operator +( const Matrix<T> &lhs, const Matrix<T> &rhs );

  template <typename T>
  Matrix<T> operator -( const Matrix<T> &lhs, const Matrix<T> &rhs );

  template <typename T>
  Matrix<T> operator *( const Matrix<T> &lhs, T val );

  template <typename T>
  Matrix<T> operator *( T val, const Matrix<T> &lhs );

  template<typename T>
  std::ostream &operator <<( std::ostream &ost, const Matrix<T> &matr );

  template <typename T>
  std::istream &operator >>( std::istream &ist, Matrix<T> &matr );

  template <typename T>
  std::istream &InputQuadr( std::istream &ist, Matrix<T> &matr );
}




template <typename T>
ad6::ldbl ad6::Matrix<T>::threshold = ad6::MAT_THRESHOLD;

template <typename T>
ad6::Matrix<T>::Matrix( int rows, int cols ) : matr_(nullptr),
                                               rows_(rows),
                                               cols_(cols)
{
  Alloc();
  Fill(T{});
}

template <typename T>
template <typename It>
ad6::Matrix<T>::Matrix( int rows, int cols, const It &begin, const It &end ) : matr_(nullptr),
                                                                               rows_(rows),
                                                                               cols_(cols)
{
  Alloc();
  size_t i = 0, size = rows_ * cols_;

  for (It it = begin; it != end && i < size; ++it, ++i)
    matr_[i / cols_][i % cols_] = *it;
}

template <typename T>
template <typename empl_func>
ad6::Matrix<T>::Matrix( int rows, int cols, empl_func fnc ) : matr_(nullptr),
                                                              rows_(rows),
                                                              cols_(cols)
{
  Alloc();
  Walker(fnc);
}

template <typename T>
template <typename walk_func>
void ad6::Matrix<T>::Walker( walk_func walk )
{
  for (size_t i = 0; i < rows_; ++i)
    for (size_t j = 0; j < cols_; ++j)
      matr_[i][j] = walk(i, j);
}

template <typename T>
ad6::Matrix<T>::Matrix( const ad6::Matrix<T> &matr ) : matr_(nullptr),
                                                       rows_(matr.rows_),
                                                       cols_(matr.cols_)
{
  Alloc();
  Copy(*this, matr);
}

template <typename T>
ad6::Matrix<T>::Matrix( ad6::Matrix<T> &&matr ) : matr_(matr.matr_),
                                                  rows_(matr.rows_),
                                                  cols_(matr.cols_)
{
  matr.matr_ = nullptr;
  matr.rows_ = matr.cols_ = 0;
}

template <typename T>
ad6::Matrix<T> & ad6::Matrix<T>::operator =( const ad6::Matrix<T> &matr )
{
  if (this == &matr)
    return *this;

  if (rows_ == matr.rows_ && cols_ == matr.cols_)
    Copy(*this, matr);
  else
  {
    Matrix tmp(matr);
    Swap(*this, tmp);
  }

  return *this;
}

template <typename T>
ad6::Matrix<T> & ad6::Matrix<T>::operator =( ad6::Matrix<T> &&matr )
{
  if (this == &matr)
    return *this;

  Matrix tmp(std::move(matr));
  Swap(*this, tmp);

  return *this;
}

template <typename T>
ad6::Matrix<T> &ad6::Matrix<T>::operator +=( const ad6::Matrix<T> &matr )
{
  assert(matr.rows_ == rows_ && matr.cols_ == cols_);

  auto add_fnc = [this, matr]( int i, int j )->T {return this->matr_[i][j] + matr.matr_[i][j];};
  Walker(add_fnc);

  return *this;
}

template <typename T>
ad6::Matrix<T> &ad6::Matrix<T>::operator -=( const ad6::Matrix<T> &matr )
{
  assert(matr.rows_ == rows_ && matr.cols_ == cols_);
  auto add_fnc = [this, matr]( int i, int j )->T {return this->matr_[i][j] - matr.matr_[i][j];};
  Walker(add_fnc);

  return *this;
}

template <typename T>
ad6::Matrix<T> &ad6::Matrix<T>::operator *=( T val )
{
  auto mul_fnc = [this, val]( int i, int j )-> T { return this->matr_[i][j] * val; };
  Walker(mul_fnc);

  return *this;
}

template <typename T>
ad6::Matrix<T> &ad6::Matrix<T>::Transpose( void )
{
  if (rows_ == cols_)
    return Transpose_Quad();

  Matrix<T> temp{cols_, rows_, [*this](int i, int j){ return this->matr_[j][i]; }};

  Swap(*this, temp);

  return *this;
}

template <typename T>
ad6::Matrix<T> ad6::Matrix<T>::Transposing( void ) const
{
  return Matrix<T>(cols_, rows_, [*this](int i, int j){ return this->matr_[j][i]; });
}

bool IsZero( ad6::ldbl val, ad6::ldbl thres )
{
  return std::abs(val) < thres;
}

template <typename T>
int ad6::Matrix<T>::FindNonZero( int st_col )
{
  for (size_t i = st_col + 1; i < cols_; ++i)
    if (!IsZero(matr_[i][st_col], threshold))
      return i;

  return -1;
}

template <typename T>
ad6::ldbl ad6::Matrix<T>::Det( void ) const
{
  if (rows_ != cols_)
    return 0;

  // check if the type is valid
  ldbl dummy = static_cast<ldbl>(matr_[0][0]);

  Matrix<T> tmp{*this};


  for (size_t i = 0; i < rows_ - 1; ++i)
  {
    if (IsZero(tmp.matr_[i][i], threshold))
    {
      int non_z_line = tmp.FindNonZero(i);
      if (non_z_line == -1)
        return 0;

      tmp.SwapLines(non_z_line, i);
    }

    T div = tmp.matr_[i][i];
    for (size_t j = i + 1; j < rows_; ++j)
      tmp.AddLineMVal(j, i, -static_cast<ldbl>(tmp.matr_[j][i]) / div);
  }

  ldbl det = 1;
  for (size_t i = 0; i < rows_; ++i)
    det *= tmp.matr_[i][i];

  return det;
}

template <typename T>
ad6::Matrix<T> ad6::Matrix<T>::Identity( int rows )
{
  Matrix id(rows, rows, []( int i, int j ) { return i == j; });

  return id;
}
template <typename T>
const T &ad6::Matrix<T>::At( int i, int j ) const
{
  int new_i = Clamp(i, 0, static_cast<int>(rows_ - 1)),
    new_j = Clamp(j, 0, static_cast<int>(cols_ - 1));

  return matr_[new_i][new_j];
}

template <typename T>
void ad6::Matrix<T>::SwapLines( int lhs, int rhs )
{
  lhs = Clamp(lhs, 0, static_cast<int>(rows_ - 1));
  rhs = Clamp(rhs, 0, static_cast<int>(rows_ - 1));

  std::swap(matr_[lhs], matr_[rhs]);
}

template <typename T>
void ad6::Matrix<T>::AddLine( int dest_ind, int src_ind )
{
  dest_ind = Clamp(dest_ind, 0, static_cast<int>(rows_ - 1));
  src_ind = Clamp(src_ind, 0, static_cast<int>(rows_ - 1));

  for (int i = 0; i < cols_; ++i)
    matr_[dest_ind][i] += matr_[src_ind][i];
}

template <typename T>
void ad6::Matrix<T>::AddLineMVal( int dest_ind, int src_ind, ldbl val )
{
  dest_ind = Clamp(dest_ind, 0, static_cast<int>(rows_ - 1));
  src_ind = Clamp(src_ind, 0, static_cast<int>(rows_ - 1));

  for (size_t i = 0; i < cols_; ++i)
    matr_[dest_ind][i] += val * matr_[src_ind][i];
}

template <typename T>
void ad6::Matrix<T>::MulLine( int line, ldbl val )
{
  line = Clamp(line, 0, static_cast<int>(rows_ - 1));

  for (int i = 0; i < cols_; ++i)
    matr_[line][i] *= val;
}

template <typename T>
ad6::Matrix<T>::~Matrix( void )
{
  for (size_t i = 0; i < rows_; ++i)
    delete[] matr_[i];

  delete[] matr_;
  matr_ = nullptr;
  rows_ = cols_ = 0;
}

template <typename T>
void ad6::Matrix<T>::Dump( std::ostream &ost ) const
{
  for (size_t i = 0; i < rows_; ++i)
  {
    ost << "|| ";
    for (size_t j = 0; j < cols_; ++j)
      ost << matr_[i][j] << (j == cols_ - 1 ? "" : ", ");
    ost << " ||\n";
  }
}

template <typename T>
void ad6::Matrix<T>::Fill( T val )
{
  for (size_t i = 0; i < rows_; ++i)
    for (size_t j = 0; j < cols_; ++j)
      matr_[i][j] = val;
}

template <typename T>
ad6::Matrix<T> &ad6::Matrix<T>::Transpose_Quad( void )
{
  for (size_t i = 0; i < cols_; ++i)
    for (size_t j = i + 1; j < cols_; ++j)
      std::swap(matr_[i][j], matr_[j][i]);

  return *this;
}

template <typename T>
void ad6::Matrix<T>::Alloc( void )
{
  matr_ = new T *[rows_];

  for (size_t i = 0; i < rows_; ++i)
    matr_[i] = new T[cols_];
}

template <typename T>
void ad6::Matrix<T>::Swap( ad6::Matrix<T> &lhs, ad6::Matrix<T> &rhs )
{
  std::swap(lhs.matr_, rhs.matr_);
  std::swap(lhs.cols_, rhs.cols_);
  std::swap(lhs.rows_, rhs.rows_);
}

/* copy matrix with idnetical sizes function */
template <typename T>
void ad6::Matrix<T>::Copy( ad6::Matrix<T> &dst, const ad6::Matrix<T> &src )
{
  for (size_t i = 0; i < dst.rows_; ++i)
    for (size_t j = 0; j < dst.cols_; ++j)
      dst.matr_[i][j] = src.matr_[i][j];
}


template <typename T>
ad6::Matrix<T> ad6::operator +( const Matrix<T> &lhs, const Matrix<T> &rhs )
{
  Matrix<T> temp{lhs};
  temp += rhs;

  return temp;
}

template <typename T>
ad6::Matrix<T> ad6::operator -( const Matrix<T> &lhs, const Matrix<T> &rhs )
{
  Matrix<T> temp{lhs};
  temp -= rhs;

  return temp;
}

template <typename T>
ad6::Matrix<T> ad6::operator *( const Matrix<T> &lhs, T val )
{
  Matrix<T> temp{lhs};
  temp *= val;

  return temp;
}

template <typename T>
ad6::Matrix<T> ad6::operator *( T val, const Matrix<T> &rhs )
{
  return rhs * val;
}

template<typename T>
std::ostream & ad6::operator <<( std::ostream &ost, const ad6::Matrix<T> &matr )
{
  matr.Dump(ost);

  return ost;
}

template <typename T>
std::istream &ad6::operator >>( std::istream &ist, Matrix<T> &matr )
{
  int rows = 0, cols = 0;
  ist >> rows >> cols;

  matr = Matrix<T>{rows, cols, [&]( int i, int j )
  {
    T val{};
    ist >> val;
    return val;
  }};

  return ist;
}

template <typename T>
std::istream &ad6::InputQuadr( std::istream &ist, Matrix<T> &matr )
{
  int size = 0;
  ist >> size;

  matr = Matrix<T>{size, size, [&]( int i, int j )
  {
    T val{};
    ist >> val;
    return val;
  }};

  return ist;
}


#endif //MATRIX_MATRIX_HPP

