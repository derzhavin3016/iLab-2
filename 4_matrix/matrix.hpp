#ifndef MATRIX_MATRIX_HPP
#define MATRIX_MATRIX_HPP

#include <iostream>
#include <cmath>
#include <cassert>


namespace ad6
{
  using ldbl = long double;

  constexpr ldbl MAT_THRESHOLD = 1e-10;

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

      const T &operator []( size_t i ) const
      {
        assert(i < m_cols);
        return m_row[i];
      }

      T &operator []( size_t i )
      {
        assert(i < m_cols);
        return m_row[i];
      }

      Row_matr( const Row_matr &row_m ) = default;

      Row_matr &operator =( const Row_matr &row_m ) = default;
    };

  public:

    Matrix( size_t rows, size_t cols );

    template <typename It>
    Matrix( size_t rows, size_t cols, It begin, It end );

    Matrix( size_t rows, size_t cols, const std::initializer_list<T> &ilist );

    template <typename empl_func>
    Matrix( size_t rows, size_t cols, empl_func fnc );

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
    Matrix &operator *=( const Matrix &matr );
    Matrix &operator *=( T val );

    Matrix &Transpose( void );

    Matrix Transposing( void ) const;

    ldbl Det( void ) const;

    size_t getCols( void ) const { return cols_; }
    size_t getRows( void ) const { return rows_; }

    static Matrix Identity( size_t rows );

    const T &At( size_t i, size_t j ) const;

    Row_matr operator []( size_t i ) const
    {
      assert(i < rows_);
      return Row_matr{cols_, matr_[i]};
    }

    Row_matr operator []( size_t i )
    {
      assert(i < rows_);
      return Row_matr{cols_, matr_[i]};
    }

    ~Matrix( void );

    void AddLineMVal( size_t dest_ind, size_t src_ind, ldbl val );

    bool IsEq( const Matrix &matr ) const;

    void Dump( std::ostream &ost ) const;

    static void SetThreshold( ldbl new_thres ) { threshold = new_thres; }
    static void SetDefThres ( void )           { threshold = MAT_THRESHOLD; }
    static ldbl GetThreshold( void )           { return threshold; }

    static bool IsZero( ldbl val ) { return std::abs(val) < threshold; }

  private:
    Matrix &Transpose_Quad( void );

    void Alloc( void );

    template <typename It>
    void FillByIt( It begin, It end );

    static void Swap( Matrix &lhs, Matrix &rhs );

    /* copy matrix with idnetical sizes function */
    static void Copy( Matrix &dst, const Matrix &src );

    void SwapLines( size_t lhs, size_t rhs );

    void AddLine( size_t dest_ind, size_t src_ind );

    void MulLine( size_t line, ldbl val );

    int FindNonZero( size_t st_col ) const;

    template <typename walk_func>
    void Walker( walk_func walk );
  };

  template <typename T>
  bool operator ==( const Matrix<T> &lhs, const Matrix<T> &rhs );

  template <typename T>
  Matrix<T> operator +( const Matrix<T> &lhs, const Matrix<T> &rhs );

  template <typename T>
  Matrix<T> operator -( const Matrix<T> &lhs, const Matrix<T> &rhs );

  template <typename T>
  Matrix<T> operator *( const Matrix<T> &lhs, const Matrix<T> &rhs );

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
ad6::Matrix<T>::Matrix( size_t rows, size_t cols ) : matr_(nullptr),
                                                     rows_(rows),
                                                     cols_(cols)
{
  Alloc();
  Walker([this]( int, int ) { return T{}; });
}

template <typename T>
template <typename It>
ad6::Matrix<T>::Matrix( size_t rows, size_t cols, It begin, It end ) : matr_(nullptr),
                                                                       rows_(rows),
                                                                       cols_(cols)
{
  Alloc();
  FillByIt(begin, end);
}

template <typename T>
ad6::Matrix<T>::Matrix( size_t rows, size_t cols, const std::initializer_list<T> &ilist ) : matr_(nullptr),
                                                                                            rows_(rows),
                                                                                            cols_(cols)
{
  Alloc();
  FillByIt(ilist.begin(), ilist.end());
}

template <typename T>
template <typename empl_func>
ad6::Matrix<T>::Matrix( size_t rows, size_t cols, empl_func fnc ) : matr_(nullptr),
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
ad6::Matrix<T> &ad6::Matrix<T>::operator *=( const Matrix &matr )
{
  assert(cols_ == matr.rows_);

  Matrix<T> temp = Transposing();

  auto mul_func = [temp, matr]( int i, int j ) -> T
    {
      T new_el = 0;
      for (size_t r = 0; r < temp.cols_; ++r)
        new_el += temp.matr_[r][i] * matr.matr_[r][j];

      return new_el;
    };
  Walker(mul_func);

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

template <typename T>
int ad6::Matrix<T>::FindNonZero( size_t st_col ) const
{
  for (size_t i = st_col + 1; i < cols_; ++i)
    if (!IsZero(matr_[i][st_col]))
      return i;

  return -1;
}

template <typename T>
ad6::ldbl ad6::Matrix<T>::Det( void ) const
{
  if (rows_ != cols_)
    return NAN;

  int sign = 1;

  // check if the type is valid
  ldbl dummy = static_cast<ldbl>(matr_[0][0]);

  Matrix<T> tmp{*this};


  for (size_t i = 0; i < rows_ - 1; ++i)
  {
    if (IsZero(tmp.matr_[i][i]))
    {
      int non_z_line = tmp.FindNonZero(i);
      if (non_z_line == -1)
        return 0;

      tmp.SwapLines(non_z_line, i);
      sign = -sign;
    }

    T div = tmp.matr_[i][i];
    for (size_t j = i + 1; j < rows_; ++j)
      tmp.AddLineMVal(j, i, -static_cast<ldbl>(tmp.matr_[j][i]) / div);
  }

  ldbl det = sign;
  for (size_t i = 0; i < rows_; ++i)
    det *= tmp.matr_[i][i];

  return det;
}

template <typename T>
ad6::Matrix<T> ad6::Matrix<T>::Identity( size_t rows )
{
  Matrix id(rows, rows, []( int i, int j ) { return i == j; });

  return id;
}
template <typename T>
const T &ad6::Matrix<T>::At( size_t i, size_t j ) const
{
  assert(i < rows_);
  assert(j < cols_);

  return matr_[i][j];
}

template <typename T>
void ad6::Matrix<T>::SwapLines( size_t lhs, size_t rhs )
{
  assert(lhs < rows_);
  assert(rhs < rows_);

  std::swap(matr_[lhs], matr_[rhs]);
}

template <typename T>
void ad6::Matrix<T>::AddLine( size_t dest_ind, size_t src_ind )
{
  assert(dest_ind < rows_);
  assert(src_ind < rows_);

  for (int i = 0; i < cols_; ++i)
    matr_[dest_ind][i] += matr_[src_ind][i];
}

template <typename T>
void ad6::Matrix<T>::AddLineMVal( size_t dest_ind, size_t src_ind, ldbl val )
{
  assert(dest_ind < rows_);
  assert(src_ind < rows_);

  for (size_t i = 0; i < cols_; ++i)
    matr_[dest_ind][i] += val * matr_[src_ind][i];
}

template <typename T>
void ad6::Matrix<T>::MulLine( size_t line, ldbl val )
{
  assert(line < rows_);

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
bool ad6::Matrix<T>::IsEq( const Matrix &matr ) const
{
  for (size_t i = 0; i < rows_; ++i)
    for (size_t j = 0; j < cols_; ++j)
      if (matr_[i][j] != matr.matr_[i][j])
        return false;

  return true;
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
template <typename It>
void ad6::Matrix<T>::FillByIt( It begin, It end )
{
  size_t i = 0, size = rows_ * cols_;

  for (It it = begin; it != end && i < size; ++it, ++i)
    matr_[i / cols_][i % cols_] = *it;
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
bool ad6::operator ==( const Matrix<T> &lhs, const Matrix<T> &rhs )
{
  return lhs.IsEq(rhs);
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
ad6::Matrix<T> ad6::operator *( const Matrix<T> &lhs, const Matrix<T> &rhs )
{
  Matrix<T> temp{lhs};
  temp *= rhs;

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
  size_t rows = 0, cols = 0;
  ist >> rows >> cols;

  matr = Matrix<T>{rows, cols, [&]( int, int )
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
  size_t size = 0;
  ist >> size;

  matr = Matrix<T>{size, size, [&]( int, int )
  {
    T val{};
    ist >> val;
    return val;
  }};

  return ist;
}


#endif //MATRIX_MATRIX_HPP

