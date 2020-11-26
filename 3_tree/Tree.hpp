#ifndef TREE_TREE_HPP
#define TREE_TREE_HPP

#include "Node.hpp"
#include "Tree_it.hpp"
#include <fstream>
#include <string>

namespace ad6
{
  template <typename T>
  class Tree final
  {
  private:
    Node<T> *root_;
    Node<T> *min_;
    Node<T> *max_;
    size_t size_;

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

    bool Empty( void ) { return size_ == 0; }

    iterator At( const T& key );

    void Clear( void );

    void DotDump( const std::string &dotname = "dump.dot",
                  const std::string &pngname = "dump.png" );

    ~Tree( void );
  private:


    [[nodiscard]] Node<T> *CreatNd( const T &key, Node<T> *par );

    [[nodiscard]] ad6::Node<T> *Insert( Node<T> *nd, const T &key );

    [[nodiscard]] Node<T> *DelMin( Node<T> *nd );

    [[nodiscard]] Node<T> *Delete( Node <T> *nd, const T &key );

    [[nodiscard]] Node<T> *Balance( Node<T> *nd );

    void MinMaxUpd( Node<T> *nd );
  };
}

template <typename T>
ad6::Tree<T>::Tree( void ) : root_(nullptr),
                             min_(nullptr),
                             max_(nullptr),
                             size_(0)
{
}

template <typename T>
void ad6::Tree<T>::Insert( const T &key )
{
  root_ = Insert(root_, key);
  ++size_;
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
    return iterator(nullptr, true);
  return iterator(max_, true);
}

template <typename T>
typename ad6::Tree<T>::const_iterator ad6::Tree<T>::begin( void ) const
{
  return const_iterator(min_);
}

template <typename T>
typename ad6::Tree<T>::const_iterator ad6::Tree<T>::end( void ) const
{
  return const_iterator(max_, false);
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
  for (int i = 0; i < size_; ++i, --it)
    std::cout << "TR[" << i << "]: " << *it << "\n";


  return it;
}

template <typename T>
void ad6::Tree<T>::Clear( void )
{
  if (root_ != nullptr)
    root_->Clear();
  delete root_;

  root_ = min_ = max_ = nullptr;
  size_ = 0;
}

template <typename T>
void ad6::Tree<T>::DotDump( const std::string &dotname /* = "dump.dot" */,
                            const std::string &pngname /* = "dump.png" */ )
{
  std::ofstream fout;
  fout.open(dotname, std::ios::out);

  if (!fout.is_open())
  {
    std::cout << "Cannot open dump file: " << dotname << "\n";
    return;
  }
  fout << "digraph D {\n";
  if (root_ != nullptr)
    root_->RecDotPrint(fout);

  fout << "}\n";
  fout.close();

  std::string promt = "dot " + dotname + " -Tpng > " + pngname;
  system(promt.c_str());
}

template <typename T>
ad6::Tree<T>::~Tree( void )
{
  Clear();
}

template <typename T>
ad6::Node<T> *ad6::Tree<T>::CreatNd( const T &key, Node<T> *par )
{
  Node<T> *new_nd = new Node<T>{key, par};
  MinMaxUpd(new_nd);
  return new_nd;
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

    Node<T> *min = right->FindMin();
    min->right_ = DelMin(right);
    min->left_ = left;
    min->parent_ = parent;

    return Balance(min);
  }

  return Balance(nd);
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
ad6::Node<T> *ad6::Tree<T>::DelMin( Node<T> *nd )
{
  if (nd->left_ == nullptr)
    return nd->right_;
  nd->left_ = nd->left_->DelMin();
  return Balance(nd);
}


#endif //TREE_TREE_HPP
