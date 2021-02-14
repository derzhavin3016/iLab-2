#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

#include <iostream>
#include <fstream>
#include <list>

namespace ad_set::detail
{
  template <typename T>
  struct Node;

  template <typename T>
  using nodelist = std::list<Node<T>>;

  template <typename T>
  using liter = typename nodelist<T>::iterator;

  template <typename T>
  const liter<T> nulit = liter<T>{};

  template <typename T>
  struct Node final
  {
    const T key_;
    int depth_;

    liter<T> left_, right_, parent_;

    Node( const T &key, liter<T> par = {}, int depth = 1, liter<T> l = {}, liter<T> r = {} );

    Node( const Node &nd ) = default;

    int GetLDepth( void ) const;
    int GetRDepth( void ) const;

    int GetBFact( void ) const;

    void UpdDepth( void );

    void RecDotPrint( std::ofstream &oft ) const;

    // Nodes rotation functions
    [[nodiscard]] liter<T> RotR( void );
    [[nodiscard]] liter<T> RotL( void );

    ~Node( void ) = default;
  };

  template <typename T>
  liter<T> FindMin( liter<T> nd );

  template <typename T>
  [[nodiscard]] liter<T> DelMin( liter<T> nd );

  template <typename T>
  [[nodiscard]] liter<T> Balance( liter<T> nd );

  template <typename T>
  liter<T> Find( liter<T> nd, const T &key );
}


template <typename T>
ad_set::detail::Node<T>::Node( const T &key, liter<T> par /* = {} */, int depth /* = 1 */,
                               liter<T> l /* = {} */, liter<T> r /* = {} */ ) : key_(key),
                                                                               depth_(depth),
                                                                               left_(l),
                                                                               right_(r),
                                                                               parent_(par)
{
}


template <typename T>
int ad_set::detail::Node<T>::GetLDepth( void ) const
{
  if (left_ == nulit<T>)
    return 0;

  return left_->depth_;
}

template <typename T>
int ad_set::detail::Node<T>::GetRDepth( void ) const
{
  if (right_ == nulit<T>)
    return 0;

  return right_->depth_;
}

template <typename T>
int ad_set::detail::Node<T>::GetBFact( void ) const
{
  return GetRDepth() - GetLDepth();
}

template <typename T>
void ad_set::detail::Node<T>::UpdDepth( void )
{
  int ldepth = GetLDepth();
  int rdepth = GetRDepth();

  depth_ = std::max(ldepth, rdepth) + 1;
}

template <typename T>
void ad_set::detail::Node<T>::RecDotPrint( std::ofstream &oft ) const
{
  if (left_ != nulit<T>)
  {
    oft << key_ << " -> " << left_->key_ << ";\n";
    left_->RecDotPrint(oft);
  }
  if (right_ != nulit<T>)
  {
    oft << key_ << " -> " << right_->key_ << ";\n";
    right_->RecDotPrint(oft);
  }
  oft << key_ << ";\n";
}

template <typename T>
ad_set::detail::liter<T> ad_set::detail::Node<T>::RotR( void )
{
  liter<T> lnd = left_;
  left_ = lnd->right_;

  if (left_ != nulit<T> && lnd->right_ != nulit<T>)
    left_->parent_ = lnd->right_->parent_;

  lnd->right_ = lnd->parent_; // this

  lnd->parent_ = parent_;
  parent_ = lnd;

  UpdDepth();
  lnd->UpdDepth();

  return lnd;
}

template <typename T>
ad_set::detail::liter<T> ad_set::detail::Node<T>::RotL( void )
{
  Node<T> *rnd = right_;
  right_ = rnd->left_;
  if (right_ != nullptr && rnd->left_ != nullptr)
    right_->parent_ = rnd->left_->parent_;

  rnd->left_ = rnd->parent_; //this

  rnd->parent_ = parent_;
  parent_ = rnd;

  UpdDepth();
  rnd->UpdDepth();

  return rnd;
}

template <typename T>
ad_set::detail::liter<T> ad_set::detail::FindMin( detail::liter<T> nd )
{
  if (nd == nulit<T>)
    return nullptr;

  if (nd->left_ == nulit<T>)
    return nd;
  
  return FindMin(nd->left_);
}

template <typename T>
ad_set::detail::liter<T> ad_set::detail::DelMin( detail::liter<T> nd )
{
  if (nd->left_ == nulit<T>)
    return nd->right_;
  nd->left_ = DelMin(nd->left_);
  return Balance(nd);
}

template <typename T>
ad_set::detail::liter<T> ad_set::detail::Balance( detail::liter<T> nd )
{
  if (nd == nulit<T>)
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
ad_set::detail::liter<T> ad_set::detail::Find( detail::liter<T> nd, const T &key )
{
  if (nd == nulit<T>)
    return nulit<T>;
  if (key < nd->key_)
    return Find(nd->left_, key);
  if (key > nd->key_)
    return Find(nd->right_, key);

  return nd;
}


#endif //TREE_NODE_HPP
