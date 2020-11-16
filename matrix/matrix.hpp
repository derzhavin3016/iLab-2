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
}



// add functions realizations
#include "matrix.ii"


#endif //MATRIX_MATRIX_HPP

