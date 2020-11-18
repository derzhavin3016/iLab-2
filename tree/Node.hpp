#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <iostream>

namespace ad6
{
  template <typename T>
  class Tree;

  template <typename T>
  class Node final
  {
  private:
    friend class Tree<T>;

    T key_;
    int depth_;

    Node *left_;
    Node *right_;

    Node( const T &key, int depth = 1, Node *l = nullptr, Node *r = nullptr );

    int GetLDepth( void ) const;
    int GetRDepth( void ) const;

    int GetBFact( void ) const;

    void UpdDepth( void );

    void Clear( void );

    ~Node( void );
  };
}

#include "Node.ii"

#endif //TREE_NODE_HPP
