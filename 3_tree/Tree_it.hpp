#ifndef TREE_TREE_IT_HPP
#define TREE_TREE_IT_HPP


#include <iostream>

namespace ad6
{
  template <typename T>
  class Node;

  template <typename T>
  class Tree_it final : public std::iterator<std::bidirectional_iterator_tag, T>
  {
  private:
    Node<T> *nd_;
    bool IsEnd;
    friend class Tree<T>;
  public:
    Tree_it( const Tree_it &tr_it ) = default;

    bool IsEq( const Tree_it &tr_ir ) const;
    bool IsnEq( const Tree_it &tr_ir ) const;

    typename Tree_it::reference operator *( void ) const;

    Tree_it &operator ++( void );
    Tree_it &operator --( void );

    const Tree_it &operator --( int );

    Node<T> *operator ->( void );

  private:
    Tree_it( Node<T> *nd = nullptr, bool IsE = false );
  };

  template <typename T>
  bool operator !=( const Tree_it<T> &lhs, const Tree_it<T> &rhs )
  {
    return lhs.IsnEq(rhs);
  }

  template <typename T>
  bool operator ==( const Tree_it<T> &lhs, const Tree_it<T> &rhs )
  {
    return lhs.IsEq(rhs);
  }
}


template <typename T>
ad6::Tree_it<T>::Tree_it( Node<T> *nd /* = nullptr */, bool IsE /* = false */ ) : nd_(nd), IsEnd(IsE)
{
}

template <typename T>
bool ad6::Tree_it<T>::IsEq( const Tree_it<T> &tr_ir ) const
{
  if (nd_ == nullptr || tr_ir.nd_ == nullptr)
    return false;

  if (IsEnd == tr_ir.IsEnd && IsEnd)
    return true;

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
  return nd_->key_;
}

template <typename T>
ad6::Tree_it<T> & ad6::Tree_it<T>::operator ++( void )
{
  if (IsEnd)
    return *this;

  if (nd_->right_ != nullptr)
    nd_ = nd_->right_;

}

template <typename T>
ad6::Tree_it<T> & ad6::Tree_it<T>::operator --( void )
{
  if (IsEnd)
  {
    IsEnd = false;
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
        }
        break;
      }
      if (new_nd->left_ == nullptr)
      {
        if (new_nd->parent_ != nullptr && old_nd != new_nd->parent_)
        {
          old_nd = new_nd;
          new_nd = new_nd->parent_;
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

#endif //TREE_TREE_IT_HPP
