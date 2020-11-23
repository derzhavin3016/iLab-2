#ifndef TREE_TREE_HPP
#define TREE_TREE_HPP

#include "Node.hpp"
#include "Tree_it.hpp"

namespace ad6
{
  template <typename T>
  class Tree final
  {
  private:
    Node<T> *root_;
    Node<T> *min_;
    Node<T> *max_;
    size_t size;

  public:
    using iterator = Tree_it<T>;
    using const_iterator = Tree_it<const T>;

    Tree( void );

    void Insert( const T &key );
    Tree<T> &operator <<( const T &key );

    iterator begin( void );
    iterator end  ( void );

    const_iterator begin( void ) const;
    const_iterator end  ( void ) const;

    void Erase( const T &key );

    bool Empty( void ) { return size == 0; }

    iterator At( const T& key );

    void Clear( void );

    ~Tree( void );
  private:

    // Nodes rotation functions
    [[nodiscard]] Node<T> *RotR( Node<T> *nd );
    [[nodiscard]] Node<T> *RotL( Node<T> *nd );

    [[nodiscard]] Node<T> *Balance( Node<T> *nd );

    [[nodiscard]] Node<T> *CreatNd( const T &key, Node<T> *par );

    [[nodiscard]] Node<T> *Insert( Node<T> *nd, const T &key );

    [[nodiscard]] Node<T> *DelMin( Node<T> *nd );

    [[nodiscard]] Node<T> *Delete( Node <T> *nd, const T &key );
    
    Node<T> *Find( Node<T> *nd, const T &key ) const;

    Node<T> *FindMin( Node<T> *nd ) const;
    Node<T> *FindMax( Node<T> *nd ) const;

    void MinMaxUpd( Node<T> *nd );
  };
}

#include "Tree.inl"

#endif //TREE_TREE_HPP
