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

  template <typename T>
  class Matrix
  {
  private:
    T **matr_;
    size_t rows_, cols_;

    // emplace function type
    //using empl_func = T (*)( int, int );

    struct Row_matr
    {
      size_t m_cols;
      const T *const m_row;

      Row_matr( size_t cols, const T *const row ) : m_cols(cols),
                                                    m_row(row)
      {}

      const T &operator []( int i ) const
      {
        return m_row[Clamp(i, 0, static_cast<int>(m_cols - 1))];
      }

      Row_matr( const Row_matr &row_m ) = default;

      Row_matr &operator =( const Row_matr &row_m ) = delete;


    };

  public:

    Matrix( int rows, int cols, T val = T{} );

    template <typename It>
    Matrix( int rows, int cols, const It &begin, const It &end );

    template <typename empl_func>
    Matrix( empl_func fnc, int rows, int cols );

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

    ~Matrix( void );

    void Dump( std::ostream &ost ) const;

  private:
    void Fill( T val );

    Matrix &Transpose_Quad( void );

    void Alloc( void );

    static void Swap( Matrix &lhs, Matrix &rhs );

    /* copy matrix with idnetical sizes function */
    static void Copy( Matrix &dst, const Matrix &src );

    template <typename empl_func>
    void EmplbFun( empl_func func );
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
#include "matrix.inl"


#endif //MATRIX_MATRIX_HPP

