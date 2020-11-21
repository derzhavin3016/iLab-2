#include "Node.hpp"

template <typename T>
ad6::Node<T>::Node( const T &key, Node *par /* = nullptr */, int depth /* = 1 */,
                    Node *l /* = nullptr */, Node *r /* = nullptr */ ) : key_(key),
                                                                                                    depth_(depth),
                                                                                                    left_(l),
                                                                                                    right_(r),
                                                                                                    parent_(par)
{
}


template <typename T>
int ad6::Node<T>::GetLDepth( void ) const
{
  if (left_ == nullptr)
    return 0;

  return left_->depth_;
}

template <typename T>
int ad6::Node<T>::GetRDepth( void ) const
{
  if (right_ == nullptr)
    return 0;

  return right_->depth_;
}

template <typename T>
int ad6::Node<T>::GetBFact( void ) const
{
  return GetRDepth() - GetLDepth();
}

template <typename T>
void ad6::Node<T>::UpdDepth( void )
{
  int ldepth = GetLDepth();
  int rdepth = GetRDepth();

  depth_ = std::max(ldepth, rdepth) + 1;
}

template <typename T>
void ad6::Node<T>::Clear( void )
{
  if (right_ != nullptr)
    right_->Clear();
  if (left_ != nullptr)
    left_->Clear();

  delete left_;
  left_ = nullptr;
  delete right_;
  right_ = nullptr;
  parent_ = nullptr;
}

template <typename T>
ad6::Node<T>::~Node( void )
{
  right_ = nullptr;
  left_ = nullptr;
  parent_ = nullptr;
}
