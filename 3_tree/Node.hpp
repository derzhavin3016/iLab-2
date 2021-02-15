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
  using csiter = typename nodelist<T>::const_iterator;

  template <typename T>
  const liter<T> nulit = liter<T>{};

  template <typename T>
  struct Node final
  {
    const T key_;
    int depth_;

    liter<T> left_, right_;

    Node( const T &key, int depth = 1, liter<T> l = {}, liter<T> r = {} );

    Node( const Node &nd ) = default;

    void RecDotPrint( std::ofstream &oft ) const;

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

  template <typename T>
  int GetLDepth( liter<T> nd );

  template <typename T>
  int GetRDepth( liter<T> nd );

  template <typename T>
  int GetBFact( liter<T> nd );

  template <typename T>
  void UpdDepth( liter<T> nd );

  // Nodes rotation functions
  template <typename T>
  [[nodiscard]] liter<T> RotR( liter<T> nd );

  template <typename T>
  [[nodiscard]] liter<T> RotL( liter<T> nd );
}


template <typename T>
ad_set::detail::Node<T>::Node( const T &key, int depth /* = 1 */,
                               liter<T> l /* = {} */, liter<T> r /* = {} */ ) : key_(key),
                                                                               depth_(depth),
                                                                               left_(l),
                                                                               right_(r)
{
}


template <typename T>
int ad_set::detail::GetLDepth( liter<T> nd )
{
  if (nd->left_ == nulit<T>)
    return 0;

  return nd->left_->depth_;
}

template <typename T>
int ad_set::detail::GetRDepth( liter<T> nd )
{
  if (nd->right_ == nulit<T>)
    return 0;

  return nd->right_->depth_;
}

template <typename T>
int ad_set::detail::GetBFact( liter<T> nd )
{
  return GetRDepth<T>(nd) - GetLDepth<T>(nd);
}

template <typename T>
void ad_set::detail::UpdDepth( liter<T> nd )
{
  int ldepth = GetLDepth<T>(nd);
  int rdepth = GetRDepth<T>(nd);

  nd->depth_ = std::max(ldepth, rdepth) + 1;
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
ad_set::detail::liter<T> ad_set::detail::RotR( liter<T> nd )
{
  liter<T> lnd = nd->left_;
  nd->left_ = lnd->right_;
  lnd->right_ = nd;

  UpdDepth<T>(nd);
  UpdDepth<T>(lnd);

  return lnd;
}

template <typename T>
ad_set::detail::liter<T> ad_set::detail::RotL( liter<T> nd )
{
  liter<T> rnd = nd->right_;
  nd->right_ = rnd->left_;
  rnd->left_ = nd; //this

  UpdDepth<T>(nd);
  UpdDepth<T>(rnd);

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

  UpdDepth<T>(nd);
  int bfact = GetBFact<T>(nd);

  if (bfact >= 2)
  {
    if (GetBFact<T>(nd->right_) < 0)
      nd->right_ = RotR<T>(nd->right_);
    return RotL<T>(nd);
  }
  if (bfact <= -2)
  {
    if (GetBFact<T>(nd->left_) > 0)
      nd->left_ = RotL<T>(nd->left_);
    return RotR<T>(nd);
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
