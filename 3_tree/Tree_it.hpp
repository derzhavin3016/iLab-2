#ifndef TREE_TREE_IT_HPP
#define TREE_TREE_IT_HPP


#include <iostream>

namespace ad_set
{
  template <typename T>
  class Tree;

  template <typename T>
  class Tree_it final : public std::iterator<std::bidirectional_iterator_tag, const T>
  {
  private:
    detail::liter<T> nd_;
    bool IsEnd;

  public:

    explicit Tree_it( detail::liter<T> nd = {}, bool IsE = false );

    Tree_it( const Tree_it &tr_it ) = default;
    Tree_it &operator =( const Tree_it &that ) = default;

    bool IsEq( const Tree_it &tr_ir ) const;
    bool IsnEq( const Tree_it &tr_ir ) const;

    typename Tree_it::reference operator *( void ) const;

    Tree_it &operator ++( void );
    Tree_it &operator --( void );

    Tree_it &operator --( int );
    Tree_it &operator ++( int );

    T *operator ->( void );
    const T *operator ->( void ) const;
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
ad_set::Tree_it<T>::Tree_it( detail::liter<T> nd /* = {} */, bool IsE /* = false */ ) : nd_(nd), IsEnd(IsE)
{
}

template <typename T>
bool ad_set::Tree_it<T>::IsEq( const Tree_it<T> &tr_ir ) const
{
  if (nd_ == detail::nulit<T> || tr_ir.nd_ == detail::nulit<T>)
    return false;

  if (tr_ir.IsEnd || IsEnd)
    return IsEnd && tr_ir.IsEnd;

  // not for end
  return nd_ == tr_ir.nd_;
}

template <typename T>
bool ad_set::Tree_it<T>::IsnEq( const Tree_it<T> &tr_ir ) const
{
  return !IsEq(tr_ir);
}

template <typename T>
typename ad_set::Tree_it<T>::reference ad_set::Tree_it<T>::operator *( void ) const
{
  return nd_->key_;
}

template <typename T>
ad_set::Tree_it<T> & ad_set::Tree_it<T>::operator ++( void )
{
  if (IsEnd)
    return *this;

  if (nd_->right_ != detail::nulit<T>)
  {
    detail::liter<T> node = nd_->right_;
    while (node->left_ != detail::nulit<T>)
      node = node->left_;
    nd_ = node;
  }
  else
  {
    /* go upper until you get a node with less key value
     * OR with nullptr (then you at the max node)
     * */

    if (nd_->parent_ == detail::nulit<T>)
      return *this;

    detail::liter<T> start_nd = nd_;
    while (nd_ != detail::nulit<T> && nd_->key_ <= start_nd->key_)
      nd_ = nd_->parent_;

    // this node is ALREADY max
    if (nd_ == detail::nulit<T>)
    {
      IsEnd = true;
      nd_ = start_nd;
    }

  }
  return *this;
}

template <typename T>
ad_set::Tree_it<T> & ad_set::Tree_it<T>::operator --( void )
{
  if (IsEnd)
  {
    IsEnd = false;
    return *this;
  }

  if (nd_->left_ != detail::nulit<T>)
  {
    detail::liter<T> node = nd_->left_;
    while (node->right_ != detail::nulit<T>)
      node = node->right_;
    nd_ = node;
  }
  else
  {
    /* go upper until you get a node with less key value
     * OR with nullptr (then you at the minimum node)
     * */

    if (nd_->parent_ == detail::nulit<T>)
      return *this;

    detail::liter<T> start_nd = nd_;
    while (nd_ != detail::nulit<T> && nd_->key_ >= start_nd->key_)
      nd_ = nd_->parent_;

    if (nd_ == detail::nulit<T>)
      nd_ = start_nd;
  }
  return *this;
}


template <typename T>
const ad_set::Tree_it<T> &ad_set::Tree_it<T>::operator --( int )
{
  Tree_it<T> tmp{*this};
  operator--();

  return tmp;
}

template <typename T>
const ad_set::Tree_it<T> &ad_set::Tree_it<T>::operator ++( int )
{
  Tree_it<T> tmp{*this};
  operator++();

  return tmp;
}

template <typename T>
T *ad_set::Tree_it<T>::operator ->( void )
{
  return &(nd_->key_);
}

template <typename T>
const T *ad_set::Tree_it<T>::operator ->( void ) const
{
  return &(nd_->key_);
}

#endif //TREE_TREE_IT_HPP
