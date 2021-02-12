#ifndef TREE_TREE_HPP
#define TREE_TREE_HPP

#include "Node.hpp"
#include "Tree_it.hpp"
#include <fstream>
#include <string>
#include <stack>

namespace adset
{
  template <typename T>
  class Tree final
  {
  private:
    detail::Node<T> *root_ = nullptr;
    detail::Node<T> *min_  = nullptr;
    detail::Node<T> *max_  = nullptr;
    size_t size_ = 0;

  public:
    using iterator = Tree_it<T>;
    using iter_n_bool = std::pair<iterator, bool>;

    Tree( void ) = default;

    Tree( const Tree &that );
    Tree( Tree &&that );

    Tree &operator =( const Tree &that );
    Tree &operator =( Tree &&that );

    iter_n_bool insert( const T &key );
    Tree<T> &operator <<( const T &key );

    iterator Find( const T &key ) const;

    iterator begin( void ) const;
    iterator end  ( void ) const;

    void Erase( iterator it );

    void Erase( const T &key );

    bool Empty( void ) { return size_ == 0; }

    size_t size( void ) { return size_; }

    void Clear( void );

    void DotDump( const std::string &pngname = "dump.png",
                  const std::string &dotname = "dump.dot" );

    ~Tree( void ) { Clear(); }

    iterator lower_bound( const T &kmin ) const;
  private:

    iterator FindLower( detail::Node<T> *nd, const T &key ) const;

    [[nodiscard]] detail::Node<T> *CreatNd( const T &key, detail::Node<T> *par, int depth = 1 );

    [[nodiscard]] adset::detail::Node<T> *Insert( detail::Node<T> *nd, const T &key, iterator &ins_it );

    [[nodiscard]] detail::Node<T> *Delete( detail::Node <T> *nd, const T &key );

    [[nodiscard]] detail::Node<T> *CopyNd( const detail::Node<T> *nd );

    void TreeDel( void );

    static void LightSwap( Tree &lhs, Tree &rhs );

    void MinMaxUpd( detail::Node<T> *nd );
  };

  template <typename T>
  std::istream &operator >>( std::istream &ist, Tree<T> &tr );
}


template <typename T>
adset::Tree<T>::Tree( const Tree &that ) : root_(),
                                           min_(),
                                           max_(),
                                           size_(that.size_)

{
  root_ = CopyNd(that.root_);
}

template <typename T>
adset::Tree<T>::Tree( Tree &&that ) : root_(that.root_),
                                      min_(that.min_),
                                      max_(that.max_),
                                      size_(that.size_)
{
  that.root_ = that.min_ = that.max_ = nullptr;
  size_ = 0;
}

template <typename T>
adset::Tree<T> &adset::Tree<T>::operator =( const Tree &that )
{
  if (this == &that)
    return *this;

  Tree tmp{that};
  LightSwap(*this, tmp);

  return *this;
}

template <typename T>
adset::Tree<T> &adset::Tree<T>::operator =( Tree &&that )
{
  if (this == &that)
    return *this;

  Tree tmp{std::move(that)};
  LightSwap(*this, tmp);

  return *this;
}

template <typename T>
typename adset::Tree<T>::iter_n_bool adset::Tree<T>::insert( const T &key )
{
  iter_n_bool pair{iterator(), false};
  size_t old_size{size_};

  root_ = Insert(root_, key, pair.first);

  if (size_ != old_size)
    pair.second = true;

  return pair;
}

template <typename T>
adset::Tree<T> &adset::Tree<T>::operator <<( const T &key )
{
  insert(key);

  return *this;
}

template <typename T>
typename adset::Tree<T>::iterator adset::Tree<T>::Find( const T &key ) const
{
  detail::Node<T> *found = detail::Find(root_, key);
  if (found == nullptr)
    return end();
  return iterator(found);
}

template <typename T>
typename adset::Tree<T>::iterator adset::Tree<T>::lower_bound( const T &kmin ) const
{
  if (kmin == min_->key_)
    return begin();

  return FindLower(root_, kmin);
}

template <typename T>
typename adset::Tree<T>::iterator adset::Tree<T>::FindLower( detail::Node<T> *nd, const T &key ) const
{
  if (nd == nullptr)
    return iterator{};
  if (key < nd->key_)
  {
    if (nd->left_ == nullptr)
      return iterator(nd);
    return FindLower(nd->left_, key);
  }
  if (key > nd->key_)
  {
    if (nd->right_ == nullptr)
      return ++iterator{nd};
    return FindLower(nd->right_, key);
  }

  return iterator(nd);
}

template <typename T>
typename adset::Tree<T>::iterator adset::Tree<T>::begin( void ) const
{
  return iterator(min_);
}

template <typename T>
typename adset::Tree<T>::iterator adset::Tree<T>::end( void ) const
{
  if (max_ == nullptr)
    return iterator(nullptr, true);
  return iterator(max_, true);
}

template <typename T>
void adset::Tree<T>::Erase( iterator it )
{
  Erase(*it);
}

template <typename T>
void adset::Tree<T>::Erase( const T &key )
{
  root_ = Delete(root_, key);
}

template <typename T>
void adset::Tree<T>::TreeDel( void )
{
  auto nd = root_;
  std::stack<detail::Node<T> *> stk{};

  while (true)
  {
    if (nd == nullptr)
    {
      if (stk.empty())
        return;
      nd = stk.top();
      stk.pop();
    }

    auto old_nd = nd;

    if (nd->right_ != nullptr)
    {
      stk.push(nd);
      nd = nd->right_;
      old_nd->right_ = nullptr;
      continue;
    }

    if (nd->left_ != nullptr)
    {
      stk.push(nd);
      nd = nd->left_;
      old_nd->left_ = nullptr;
      continue;
    }

    delete nd;
    nd = nullptr;
  }
}

template <typename T>
void adset::Tree<T>::Clear( void )
{
  if (root_ != nullptr)
    TreeDel();

  root_ = nullptr;
  min_ = max_ = nullptr;
  size_ = 0;
}

template <typename T>
void adset::Tree<T>::DotDump( const std::string &pngname /* = "dump.png" */,
                              const std::string &dotname /* = "dump.dot" */ )
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
adset::detail::Node<T> *adset::Tree<T>::CreatNd( const T &key, detail::Node<T> *par, int depth /* = 1 */ )
{
  auto new_nd = new detail::Node<T>{key, par, depth};
  MinMaxUpd(new_nd);
  return new_nd; 
}

template <typename T>
void adset::Tree<T>::MinMaxUpd( detail::Node<T> *nd )
{
  if (min_ == nullptr) // max is also nullptr
    max_ = min_ = nd;
  else if (nd->key_ > max_->key_)
    max_ = nd;
  else if (nd->key_ < min_->key_)
    min_ = nd;
}

template <typename T>
adset::detail::Node<T> *adset::Tree<T>::Insert( detail::Node<T> *nd, const T &key, iterator &ins_it )
{
  // for future////////////////////
  /*
  detail::Node<T> *nd_p = nullptr;
  detail::Node<T> *nd_old = nd;

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
  {
    // Here we can caught an exception
    auto new_node = CreatNd(key, nullptr);

    ++size_;
    ins_it = iterator(new_node);
    return new_node;
  }

  if (key < nd->key_)
  {
    nd->left_ = Insert(nd->left_, key, ins_it);
    nd->left_->parent_ = nd;
  }
  else if (key > nd->key_)
  {
    nd->right_ = Insert(nd->right_, key, ins_it);
    nd->right_->parent_ = nd;
  }
  else
  {
    ins_it = iterator(nd);
    return nd;
  }

  return detail::Balance(nd);
}

template <typename T>
adset::detail::Node<T> *adset::Tree<T>::Delete( detail::Node <T> *nd, const T &key )
{
  if (nd == nullptr)
    return nullptr;
  if (key < nd->key_)
    nd->left_ = Delete(nd->left_, key);
  else if (key > nd->key_)
    nd->right_ = Delete(nd->right_, key);
  else // key == nd->key_
  {
    auto left = nd->left_;
    auto right = nd->right_;
    auto parent = nd->parent_;

    if (nd == max_)
    {
      if (left != nullptr)
        max_ = left;
      else if (parent != nullptr)
        max_ = parent;
      else
        max_ = nullptr;
    }

    if (nd == min_)
    {
      if (right != nullptr)
        min_ = right;
      else if (parent != nullptr)
        min_ = parent;
      else
        min_ = nullptr;
    }


    delete nd; // deleting required node
    --size_;

    if (right == nullptr)
      return left;

    auto min = detail::FindMin(right);
    min->right_ = DelMin(right);
    min->left_ = left;
    min->parent_ = parent;

    return detail::Balance(min);
  }

  return detail::Balance(nd);
}

template <typename T>
adset::detail::Node<T> *adset::Tree<T>::CopyNd( const detail::Node<T> *nd )
{
  if (nd == nullptr)
    return nullptr;
/*
  auto tmp_root =

  while (true)
  {
    if (nd->right_ != nullptr)
    {

    }

    if (nd->left_ != nullptr)
    {

    }
  }*/
  auto tmp = CreatNd(nd->key_, nd->parent_, nd->depth_);

  tmp->right_ = CopyNd(nd->right_);
  tmp->left_  = CopyNd(nd->left_);

  return tmp;
}

template <typename T>
void adset::Tree<T>::LightSwap( Tree &lhs, Tree &rhs )
{
  std::swap(lhs.root_, rhs.root_);
  std::swap(lhs.min_, rhs.min_);
  std::swap(lhs.max_, rhs.max_);
  std::swap(lhs.size_, rhs.size_);
}

template <typename T>
std::istream &adset::operator >>( std::istream &ist, adset::Tree<T> &tr )
{
  size_t size = 0;
  ist >> size;
  T elem{};

  for (size_t i = 0; i < size; ++i)
  {
    ist >> elem;
    tr.insert(elem);
  }

  return ist;
}

#endif //TREE_TREE_HPP
