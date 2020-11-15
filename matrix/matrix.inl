template <typename T>
ad6::Matrix<T>::Matrix( int rows, int cols, T val /* = T{} */ ) : matr_(nullptr),
                                                                  rows_(rows),
                                                                  cols_(cols)
{
  Alloc();
  Fill(val);
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
  EmplbFun(fnc);
}

template <typename T>
template <typename empl_func>
void ad6::Matrix<T>::EmplbFun( empl_func func )
{
  for (size_t i = 0; i < rows_; ++i)
    for (size_t j = 0; j < cols_; ++j)
      matr_[i][j] = func(i, j);
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
  EmplbFun(add_fnc);
  
  return *this;
}

template <typename T>
ad6::Matrix<T> &ad6::Matrix<T>::operator -=( const ad6::Matrix<T> &matr )
{
  assert(matr.rows_ == rows_ && matr.cols_ == cols_);
  auto add_fnc = [this, matr]( int i, int j )->T {return this->matr_[i][j] - matr.matr_[i][j];};
  EmplbFun(add_fnc);

  return *this;
}

template <typename T>
ad6::Matrix<T> &ad6::Matrix<T>::operator *=( T val )
{
  auto mul_fnc = [this, val]( int i, int j )-> T { return this->matr_[i][j] * val; };
  EmplbFun(mul_fnc);

  return *this;
}

template <typename T>
ad6::Matrix<T> &ad6::Matrix<T>::Transpose( void )
{
  if (rows_ == cols_)
    return Transpose_Quad();
  return *this;
}

// TODO: emplacer-func constructor
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

  return std::move(temp);
}

template <typename T>
ad6::Matrix<T> ad6::operator -( const Matrix<T> &lhs, const Matrix<T> &rhs )
{
  Matrix<T> temp{lhs};
  temp -= rhs;

  return std::move(temp);
}

template <typename T>
ad6::Matrix<T> ad6::operator *( const Matrix<T> &lhs, T val )
{
  Matrix<T> temp{lhs};
  temp *= val;

  return std::move(temp);
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