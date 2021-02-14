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

  public:

    Tree_it( detail::liter<T> nd = {} );

    Tree_it( const Tree_it &tr_it ) = default;
    Tree_it &operator =( const Tree_it &that ) = default;

    bool IsEq( const Tree_it &tr_ir ) const;
    bool IsnEq( const Tree_it &tr_ir ) const;

    typename Tree_it::reference operator *( void ) const;

    Tree_it &operator ++( void );
    Tree_it &operator --( void );

    const Tree_it &operator --( int );
    const Tree_it &operator ++( int );

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
ad_set::Tree_it<T>::Tree_it( detail::liter<T> nd /* = {} */ ) : nd_(nd)
{
}

template <typename T>
bool ad_set::Tree_it<T>::IsEq( const Tree_it<T> &tr_ir ) const
{
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
  ++nd_;
  return *this;
}

template <typename T>
ad_set::Tree_it<T> & ad_set::Tree_it<T>::operator --( void )
{
  --nd_;
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
