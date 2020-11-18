#ifndef TREE_TREE_HPP
#define TREE_TREE_HPP

#include "Node.hpp"

#define ALLOC_NODISC [[nodiscard]]

namespace ad6
{
  template <typename T>
  class Tree final
  {
  private:
    Node<T> *root_;
    size_t size;
  public:
    Tree( void );

    void Insert( const T &key );
    Tree<T> &operator <<( const T &key );

    void Erase( const T &key );

    bool Empty( void ) { return size == 0; }

    void Clear( void );

    ~Tree( void );
  private:

    // Nodes rotation functions
    ALLOC_NODISC Node<T> *RotR( Node<T> *nd );
    ALLOC_NODISC Node<T> *RotL( Node<T> *nd );

    ALLOC_NODISC Node<T> *Balance( Node<T> *nd );

    ALLOC_NODISC Node<T> *Insert( Node<T> *nd, const T &key );

    ALLOC_NODISC Node<T> *FindMin( Node<T> *nd );

    ALLOC_NODISC Node<T> *DelMin( Node<T> *nd );

    ALLOC_NODISC Node<T> *Delete( Node <T> *nd, const T &key );
  };
}

#include "Tree.ii"

#endif //TREE_TREE_HPP
