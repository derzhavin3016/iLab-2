#include "Tree.hpp"

template <typename T>
ad6::Tree<T>::Tree( void ) : root_(nullptr),
                             min_(nullptr),
                             max_(nullptr),
                             size(0)
{
}

template <typename T>
void ad6::Tree<T>::Insert( const T &key )
{
  root_ = Insert(root_, key);
  ++size;
}

template <typename T>
ad6::Tree<T> &ad6::Tree<T>::operator <<( const T &key )
{
  Insert(key);

  return *this;
}

template <typename T>
typename ad6::Tree<T>::iterator ad6::Tree<T>::begin( void )
{
  return iterator(min_);
}

template <typename T>
typename ad6::Tree<T>::iterator ad6::Tree<T>::end( void )
{
  if (max_ == nullptr)
    return iterator();
  return iterator(max_->right_);
}

template <typename T>
typename ad6::Tree<T>::const_iterator ad6::Tree<T>::begin( void ) const
{
  return const_iterator(min_);
}

template <typename T>
typename ad6::Tree<T>::const_iterator ad6::Tree<T>::end( void ) const
{
  return const_iterator(max_ + 1);
}

template <typename T>
void ad6::Tree<T>::Erase( const T &key )
{
  root_ = Delete(root_, key);
}

template <typename T>
typename ad6::Tree<T>::iterator ad6::Tree<T>::At( const T& key )
{
  iterator it = --end();
  for (int i = 0; i < size; ++i)
  {
    std::cout << "Nd[" << i << "]: " << it.nd_->key_ << "\n";
    //--it;
  }
  return it;
}

template <typename T>
void ad6::Tree<T>::Clear( void )
{
  if (root_ != nullptr)
    root_->Clear();
  delete root_;

  root_ = min_ = max_ = nullptr;
  size = 0;
}

template <typename T>
ad6::Tree<T>::~Tree( void )
{
  Clear();
}

template <typename T>
ad6::Node<T> *ad6::Tree<T>::RotR( Node<T> *nd )
{
  Node<T> *lnd = nd->left_;
  nd->left_ = lnd->right_;
  if (nd->left_ != nullptr)
    nd->left_->parent_ = lnd->right_->parent_;

  lnd->right_ = nd;

  lnd->parent_ = nd->parent_;
  nd->parent_ = lnd;

  nd->UpdDepth();
  lnd->UpdDepth();

  return lnd;
}

template <typename T>
ad6::Node<T> *ad6::Tree<T>::RotL( Node<T> *nd )
{
  Node<T> *rnd = nd->right_;
  nd->right_ = rnd->left_;
  nd->right_->parent_ = rnd->left_->parent_;

  rnd->left_ = nd;

  rnd->parent_ = nd->parent_;
  nd->parent_ = rnd;

  nd->UpdDepth();
  rnd->UpdDepth();

  return rnd;
}

template <typename T>
ad6::Node<T> *ad6::Tree<T>::Balance( Node<T> *nd )
{
  if (nd == nullptr)
    return nd;

  nd->UpdDepth();
  int bfact = nd->GetBFact();

  if (bfact >= 2)
  {
    if (nd->right_->GetBFact() < 0)
      nd->right_ = RotR(nd->right_);
    return RotL(nd);
  }
  if (bfact <= -2)
  {
    if (nd->left_->GetBFact() > 0)
      nd->left_ = RotL(nd->left_);
    return RotR(nd);
  }
  return nd;
}

template <typename T>
void ad6::Tree<T>::MinMaxUpd( Node<T> *nd )
{
  if (min_ == nullptr)
    max_ = min_ = nd;
  else if (nd->key_ > max_->key_)
    max_ = nd;
  else if (nd->key_ < min_->key_)
    min_ = nd;
}

template <typename T>
ad6::Node<T> *ad6::Tree<T>::CreatNd( const T &key, Node<T> *par )
{
  Node<T> *new_nd = new Node<T>{key, par};
  MinMaxUpd(new_nd);
  return new_nd;
}

template <typename T>
ad6::Node<T> *ad6::Tree<T>::Insert( Node<T> *nd, const T &key )
{
  // for future////////////////////
  /*
  Node<T> *nd_p = nullptr;
  Node<T> *nd_old = nd;

  while (1)
  {
    if (nd == nullptr)
    {
      nd = CreatNd(key, nd_p);
      return nd_old;
    }

    if (key < nd->key_)
    {
      nd_p = nd;
      nd = nd->left_;
    }
    else if (key > nd->key_)
    {
      nd_p = nd;
      nd = nd->right_;
    }
    else
      return nd_old;

    nd = Balance(nd);
  }*/
  ////////////////////////////////

  if (nd == nullptr)
    return CreatNd(key, nullptr);

  if (key < nd->key_)
  {
    nd->left_ = Insert(nd->left_, key);
    nd->left_->parent_ = nd;
  }
  else if (key > nd->key_)
  {
    nd->right_ = Insert(nd->right_, key);
    nd->right_->parent_ = nd;
  }
  else
    return nd;

  return Balance(nd);
}

template <typename T>
ad6::Node<T> *ad6::Tree<T>::FindMin( Node<T> *nd ) const
{
  if (nd == nullptr)
    return nd;
  return FindMin(nd->left_);
}

template <typename T>
ad6::Node<T> *ad6::Tree<T>::FindMax( Node<T> *nd ) const
{
  if (nd == nullptr)
    return nd;
  return FindMax(nd->right_);
}

template <typename T>
ad6::Node<T> *ad6::Tree<T>::DelMin( Node<T> *nd )
{
  if (nd->left_ == nullptr)
    return nd->right_;
  nd->left_ = DelMin(nd->left_);
  return Balance(nd);
}

template <typename T>
ad6::Node<T> *ad6::Tree<T>::Delete( Node <T> *nd, const T &key )
{
  if (nd == nullptr)
    return nullptr;
  if (key < nd->key_)
    nd->left_ = Delete(nd->left_, key);
  else if (key > nd->key_)
    nd->right_ = Delete(nd->right_, key);
  else // key == nd->key_
  {
    Node<T> *left = nd->left_;
    Node<T> *right = nd->right_;
    Node<T> *parent = nd->parent_;
    delete nd;

    if (right == nullptr)
      return left;

    Node<T> *min = FindMin(right);
    min->right_ = DelMin(right);
    min->left_ = left;
    min->parent_ = parent;

    return Balance(min);
  }

  return Balance(nd);
}

template <typename T>
ad6::Node<T> *ad6::Tree<T>::Find( Node<T> *nd, const T &key ) const
{
  if (nd == nullptr)
    return nullptr;
  if (key < nd->key_)
    return Find(nd->left_, key);
  if (key > nd->key_)
    return Find(nd->right_, key);

  return nd;
}
