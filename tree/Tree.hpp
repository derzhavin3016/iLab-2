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
  };
}

#include "Tree.ii"

#endif //TREE_TREE_HPP
