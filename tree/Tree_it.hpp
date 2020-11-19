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

#include "Tree_it.ii"

#endif //TREE_TREE_IT_HPP
