#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <iostream>
#include <fstream>

namespace adset::detail
{
  template <typename T>
  struct Node final
  {
    const T key_;
    int depth_;

    Node *left_;
    Node *right_;
    Node *parent_;

    Node( const T &key, Node *par = nullptr, int depth = 1, Node *l = nullptr, Node *r = nullptr );

    Node( const Node &nd ) = default;

    int GetLDepth( void ) const;
    int GetRDepth( void ) const;

    int GetBFact( void ) const;

    void UpdDepth( void );

    void Clear( void );

    void RecDotPrint( std::ofstream &oft ) const;

    // Nodes rotation functions
    [[nodiscard]] Node<T> *RotR( void );
    [[nodiscard]] Node<T> *RotL( void );

    ~Node( void ) = default;
  };

  template <typename T>
  Node<T> *FindMin( Node<T> *nd );

  template <typename T>
  [[nodiscard]] Node<T> *DelMin( Node<T> *nd );

  template <typename T>
  [[nodiscard]] Node<T> *Balance( Node<T> *nd );

  template <typename T>
  Node<T> *Find( Node<T> *nd, const T &key );
}


template <typename T>
adset::detail::Node<T>::Node( const T &key, Node *par /* = nullptr */, int depth /* = 1 */,
                              Node *l /* = nullptr */, Node *r /* = nullptr */ ) : key_(key),
                                                                         depth_(depth),
                                                                         left_(l),
                                                                         right_(r),
                                                                         parent_(par)
{
}


template <typename T>
int adset::detail::Node<T>::GetLDepth( void ) const
{
  if (left_ == nullptr)
    return 0;

  return left_->depth_;
}

template <typename T>
int adset::detail::Node<T>::GetRDepth( void ) const
{
  if (right_ == nullptr)
    return 0;

  return right_->depth_;
}

template <typename T>
int adset::detail::Node<T>::GetBFact( void ) const
{
  return GetRDepth() - GetLDepth();
}

template <typename T>
void adset::detail::Node<T>::UpdDepth( void )
{
  int ldepth = GetLDepth();
  int rdepth = GetRDepth();

  depth_ = std::max(ldepth, rdepth) + 1;
}

template <typename T>
void adset::detail::Node<T>::Clear( void )
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
void adset::detail::Node<T>::RecDotPrint( std::ofstream &oft ) const
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
adset::detail::Node<T> *adset::detail::Node<T>::RotR( void )
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
adset::detail::Node<T> *adset::detail::Node<T>::RotL( void )
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
adset::detail::Node<T> *adset::detail::FindMin( detail::Node<T> *nd )
{
  if (nd == nullptr)
    return nullptr;

  if (nd->left_ == nullptr)
    return nd;
  
  return FindMin(nd->left_);
}

template <typename T>
adset::detail::Node<T> *adset::detail::DelMin( detail::Node<T> *nd )
{
  if (nd->left_ == nullptr)
    return nd->right_;
  nd->left_ = DelMin(nd->left_);
  return Balance(nd);
}

template <typename T>
adset::detail::Node<T> *adset::detail::Balance( detail::Node<T> *nd )
{
  if (nd == nullptr)
    return nd;

  nd->UpdDepth();
  int bfact = nd->GetBFact();

  if (bfact >= 2)
  {
    if (nd->right_->GetBFact() < 0)
      nd->right_ = nd->right_->RotR();
    return nd->RotL();
  }
  if (bfact <= -2)
  {
    if (nd->left_->GetBFact() > 0)
      nd->left_ = nd->left_->RotL();
    return nd->RotR();
  }
  return nd;
}

template <typename T>
adset::detail::Node<T> *adset::detail::Find( detail::Node<T> *nd, const T &key )
{
  if (nd == nullptr)
    return nullptr;
  if (key < nd->key_)
    return Find(nd->left_, key);
  if (key > nd->key_)
    return Find(nd->right_, key);

  return nd;
}


#endif //TREE_NODE_HPP
