#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <iostream>
#include <fstream>

namespace ad6
{
  template <typename T>
  class Tree;

  template <typename T>
  class Tree_it;

  template <typename T>
  class Node final
  {
  private:
    friend class Tree<T>;
    friend class Tree_it<T>;

    T key_;
    int depth_;

    Node *left_;
    Node *right_;
    Node *parent_;

    Node( const T &key, Node *par = nullptr, int depth = 1, Node *l = nullptr, Node *r = nullptr );

    Node( const Node &nd ) = default;
    Node &operator =( const Node &nd ) = default;

    int GetLDepth( void ) const;
    int GetRDepth( void ) const;

    int GetBFact( void ) const;

    void UpdDepth( void );

    void Clear( void );

    void RecDotPrint( std::ofstream &oft );

    // Nodes rotation functions
    [[nodiscard]] Node<T> *RotR( void );
    [[nodiscard]] Node<T> *RotL( void );

    Node<T> *FindMin( void ) const;
    Node<T> *FindMax( void ) const;

    ~Node( void );
  };
}


template <typename T>
ad6::Node<T>::Node( const T &key, Node *par /* = nullptr */, int depth /* = 1 */,
                    Node *l /* = nullptr */, Node *r /* = nullptr */ ) : key_(key),
                                                                         depth_(depth),
                                                                         left_(l),
                                                                         right_(r),
                                                                         parent_(par)
{
}


template <typename T>
int ad6::Node<T>::GetLDepth( void ) const
{
  if (left_ == nullptr)
    return 0;

  return left_->depth_;
}

template <typename T>
int ad6::Node<T>::GetRDepth( void ) const
{
  if (right_ == nullptr)
    return 0;

  return right_->depth_;
}

template <typename T>
int ad6::Node<T>::GetBFact( void ) const
{
  return GetRDepth() - GetLDepth();
}

template <typename T>
void ad6::Node<T>::UpdDepth( void )
{
  int ldepth = GetLDepth();
  int rdepth = GetRDepth();

  depth_ = std::max(ldepth, rdepth) + 1;
}

template <typename T>
void ad6::Node<T>::Clear( void )
{
  if (right_ != nullptr)
    right_->Clear();
  if (left_ != nullptr)
    left_->Clear();

  delete left_;
  left_ = nullptr;
  delete right_;
  right_ = nullptr;
  parent_ = nullptr;
}

template <typename T>
void ad6::Node<T>::RecDotPrint( std::ofstream &oft )
{
  if (left_ != nullptr)
  {
    oft << key_ << " -> " << left_->key_ << ";\n";
    left_->RecDotPrint(oft);
  }
  if (right_ != nullptr)
  {
    oft << key_ << " -> " << right_->key_ << ";\n";
    right_->RecDotPrint(oft);
  }
  oft << key_ << ";\n";
}

template <typename T>
ad6::Node<T> *ad6::Node<T>::RotR( void )
{
  Node<T> *lnd = left_;
  left_ = lnd->right_;

  if (left_ != nullptr && lnd->right_ != nullptr)
    left_->parent_ = lnd->right_->parent_;

  lnd->right_ = this;

  lnd->parent_ = parent_;
  parent_ = lnd;

  UpdDepth();
  lnd->UpdDepth();

  return lnd;
}

template <typename T>
ad6::Node<T> *ad6::Node<T>::RotL( void )
{
  Node<T> *rnd = right_;
  right_ = rnd->left_;
  if (right_ != nullptr && rnd->left_ != nullptr)
    right_->parent_ = rnd->left_->parent_;

  rnd->left_ = this;

  rnd->parent_ = parent_;
  parent_ = rnd;

  UpdDepth();
  rnd->UpdDepth();

  return rnd;
}

template <typename T>
ad6::Node<T> *ad6::Node<T>::FindMin( void ) const
{
  if (this == nullptr)
    return this;
  return left_->FindMin();
}

template <typename T>
ad6::Node<T> *ad6::Node<T>::FindMax( void ) const
{
  if (this == nullptr)
    return this;
  return right_->FindMax();
}

template <typename T>
ad6::Node<T>::~Node( void )
{
  right_ = nullptr;
  left_ = nullptr;
  parent_ = nullptr;
}


#endif //TREE_NODE_HPP
