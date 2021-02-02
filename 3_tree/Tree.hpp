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
    detail::Node<T> *root_ = nullptr;
    detail::Node<T> *min_  = nullptr;
    detail::Node<T> *max_  = nullptr;
    size_t size_ = 0;

    using iterator = Tree_it<T>;

  public:
    using iter_n_bool = std::pair<iterator, bool>;

    Tree( void );

    iter_n_bool insert( const T &key );
    Tree<T> &operator <<( const T &key );

    iterator Find( const T &key );
    iterator Find( const T &key ) const;

    iterator begin( void ) const;
    iterator end  ( void ) const;

    void Erase( const T &key );

    bool Empty( void ) { return size_ == 0; }

    void Clear( void );

    void DotDump( const std::string &dotname = "dump.dot",
                  const std::string &pngname = "dump.png" );

    ~Tree( void );

    iterator lower_bound( const T &kmin ) const;
  private:

    iterator FindNear( detail::Node<T> *nd, const T &key ) const;

    [[nodiscard]] detail::Node<T> *CreatNd( const T &key, detail::Node<T> *par );

    [[nodiscard]] ad6::detail::Node<T> *Insert( detail::Node<T> *nd, const T &key, iterator &ins_it );

    [[nodiscard]] detail::Node<T> *Delete( detail::Node <T> *nd, const T &key );

    void MinMaxUpd( detail::Node<T> *nd );
  };

  template <typename T>
  std::istream &operator >>( std::istream &ist, Tree<T> &tr )
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
}

template <typename T>
ad6::Tree<T>::Tree( void )
{
}

template <typename T>
typename ad6::Tree<T>::iter_n_bool ad6::Tree<T>::insert( const T &key )
{
  iter_n_bool pair{iterator(), false};
  size_t old_size{size_};

  root_ = Insert(root_, key, pair.first);

  if (size_ != old_size)
    pair.second = true;

  return pair;
}

template <typename T>
ad6::Tree<T> &ad6::Tree<T>::operator <<( const T &key )
{
  insert(key);

  return *this;
}

template <typename T>
typename ad6::Tree<T>::iterator ad6::Tree<T>::Find( const T &key )
{
  detail::Node<T> *found = Find(root_, key);
  if (found == nullptr)
    return end();
  return iterator(found);
}

template <typename T>
typename ad6::Tree<T>::iterator ad6::Tree<T>::Find( const T &key ) const
{
  detail::Node<T> *found = Find(root_, key);
  if (found == nullptr)
    return end();
  return iterator(found);
}

template <typename T>
typename ad6::Tree<T>::iterator ad6::Tree<T>::lower_bound( const T &kmin ) const
{
  if (kmin == min_->key_)
    return ++begin();

  return FindNear(root_, kmin);
}

template <typename T>
typename ad6::Tree<T>::iterator ad6::Tree<T>::FindNear( detail::Node<T> *nd, const T &key ) const
{
  if (nd == nullptr)
    return nullptr;
  if (key < nd->key_)
  {
    if (nd->left_ == nullptr)
      return iterator(nd);
    return FindNear(nd->left_, key);
  }
  if (key > nd->key_)
  {
    if (nd->right_ == nullptr)
      return nd == max_ ? end() : iterator(nd);
    return FindNear(nd->right_, key);
  }

  return iterator(nd);
}

template <typename T>
typename ad6::Tree<T>::iterator ad6::Tree<T>::begin( void ) const
{
  return iterator(min_);
}

template <typename T>
typename ad6::Tree<T>::iterator ad6::Tree<T>::end( void ) const
{
  if (max_ == nullptr)
    return iterator(nullptr, true);
  return iterator(max_, true);
}

template <typename T>
void ad6::Tree<T>::Erase( const T &key )
{
  root_ = Delete(root_, key);
  // TODO: min, max ?
}

template <typename T>
void ad6::Tree<T>::Clear( void )
{
  if (root_ != nullptr)
    root_->Clear();
  delete root_;

  root_ = nullptr;
  min_ = max_ = nullptr;
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
ad6::detail::Node<T> *ad6::Tree<T>::CreatNd( const T &key, detail::Node<T> *par )
{
  detail::Node<T> *new_nd = new detail::Node<T>{key, par};
  MinMaxUpd(new_nd);
  return new_nd; 
}

template <typename T>
void ad6::Tree<T>::MinMaxUpd( detail::Node<T> *nd )
{
  if (min_ == nullptr)
    max_ = min_ = nd;
  else if (nd->key_ > max_->key_)
    max_ = nd;
  else if (nd->key_ < min_->key_)
    min_ = nd;
}

template <typename T>
ad6::detail::Node<T> *ad6::Tree<T>::Insert( detail::Node<T> *nd, const T &key, iterator &ins_it )
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
    detail::Node<T> *new_node = CreatNd(key, nullptr);

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

  return Balance(nd);
}

template <typename T>
ad6::detail::Node<T> *ad6::Tree<T>::Delete( detail::Node <T> *nd, const T &key )
{
  if (nd == nullptr)
    return nullptr;
  if (key < nd->key_)
    nd->left_ = Delete(nd->left_, key);
  else if (key > nd->key_)
    nd->right_ = Delete(nd->right_, key);
  else // key == nd->key_
  {
    detail::Node<T> *left = nd->left_;
    detail::Node<T> *right = nd->right_;
    detail::Node<T> *parent = nd->parent_;
    delete nd; // deleting required node

    //if (nd == max_)

    if (right == nullptr)
      return left;

    auto min = detail::FindMin(right);
    min->right_ = DelMin(right);
    min->left_ = left;
    min->parent_ = parent;

    return Balance(min);
  }

  return Balance(nd);
}


#endif //TREE_TREE_HPP
