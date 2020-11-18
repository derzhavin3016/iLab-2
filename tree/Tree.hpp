#ifndef TREE_TREE_HPP
#define TREE_TREE_HPP

#include "Node.hpp"

namespace ad6
{
  template <typename T>
  class Tree final
  {
  private:
    Node<T> *root_;

  public:
    Tree( void );

    ~Tree( void );
  private:

    // Nodes rotation functions
    Node<T> *RotR( Node<T> *nd );
    Node<T> *RotL( Node<T> *nd );

    Node<T> *Balance( Node<T> *nd );

    Node<T> *Indert( Node<T> *nd );
  };
}

#include "Tree.ii"

#endif //TREE_TREE_HPP
