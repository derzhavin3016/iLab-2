#include "Tree_it.hpp"

template <typename T>
ad6::Tree_it<T>::Tree_it( Node<T> *nd /* = nullptr */, bool IsE /* = false */ ) : nd_(nd), IsEnd(IsE)
{
}

template <typename T>
bool ad6::Tree_it<T>::IsEq( const Tree_it<T> &tr_ir ) const
{
  if (nd_ == nullptr || tr_ir.nd_ == nullptr)
    return false;

  return nd_ == tr_ir.nd_;
}

template <typename T>
bool ad6::Tree_it<T>::IsnEq( const Tree_it<T> &tr_ir ) const
{
  return !IsEq(tr_ir);
}

template <typename T>
typename ad6::Tree_it<T>::reference ad6::Tree_it<T>::operator *( void ) const
{
  return *nd_;
}

template <typename T>
ad6::Tree_it<T> & ad6::Tree_it<T>::operator ++( void )
{

}

template <typename T>
ad6::Tree_it<T> & ad6::Tree_it<T>::operator --( void )
{
  if (IsEnd)
  {
    --nd_;
    return *this;
  }

  if (nd_->left_ != nullptr)
    nd_ = nd_->left_;
  else
  {
    Node<T> *new_nd = nd_;
    Node<T> *old_nd = nullptr;

    while (1)
    {
      // the node is a root
      if (new_nd->parent_ == nullptr)
      {
        if (new_nd->left_ != nullptr && old_nd != new_nd->left_)
        {
          old_nd = new_nd;
          new_nd = new_nd->left_;
          continue;
        }
        break;
      }
      if (new_nd->left_ == nullptr)
      {
        if (new_nd->parent_ != nullptr && old_nd != new_nd->parent_)
        {
          old_nd = new_nd;
          new_nd = new_nd->parent_;
          continue;
        }
        break;
      }

      old_nd = new_nd;
      new_nd = new_nd->left_;
    }
    nd_ = new_nd;
  }

  return *this;
}


template <typename T>
const ad6::Tree_it<T> &ad6::Tree_it<T>::operator --( int )
{

}

template <typename T>
ad6::Node<T> *ad6::Tree_it<T>::operator ->( void )
{

}

