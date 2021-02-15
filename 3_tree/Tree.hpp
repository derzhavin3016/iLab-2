#ifndef TREE_TREE_HPP
#define TREE_TREE_HPP

#include "Node.hpp"
#include "Tree_it.hpp"
#include <fstream>
#include <string>
#include <list>

namespace ad_set
{
  template <typename T>
  class Tree final
  {
  private:
    // useful aliases
    using ndlist = detail::nodelist<T>;
    using lit = detail::liter<T>;
    using cslit = detail::csiter<T>;

    const lit nulit = detail::nulit<T>;

    // list with nodes_
    ndlist nodes_;

    // iterator to tree's root
    lit root_{};

    // using list for inserting/deleting data in/from any place by O(1)


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

    iterator find( const T &key ) const;

    iterator begin( void ) const;
    iterator end  ( void ) const;

    void erase( iterator it );

    void erase( const T &key );

    bool empty( void ) { return nodes_.size() == 0; }

    void clear( void ) { root_ = {}; nodes_.clear(); }

    size_t size( void ) { return nodes_.size(); }

    void DotDump( const std::string &pngname = "dump.png",
                  const std::string &dotname = "dump.dot" );

    ~Tree( void ) = default;

    iterator lower_bound( const T &kmin ) const;
  private:

    iterator FindLower( lit nd, const T &key ) const;

    [[nodiscard]] lit Insert( lit nd, const T &key, iterator &ins_it );

    [[nodiscard]] lit Delete( lit nd, const T &key );

    [[nodiscard]] lit CopyNd( lit nd, lit parent );
  };

  template <typename T>
  std::istream &operator >>( std::istream &ist, Tree<T> &tr );
}


template <typename T>
ad_set::Tree<T>::Tree( const Tree &that ) : nodes_(),
                                            root_(CopyNd(that.root_, lit{}))
{}

template <typename T>
ad_set::Tree<T>::Tree( Tree &&that ) : nodes_(std::move(that.nodes_)),
                                       root_(that.root_)
{
}

template <typename T>
ad_set::Tree<T> &ad_set::Tree<T>::operator =( const Tree &that )
{
  if (this == &that)
    return *this;

  Tree tmp{that};
  std::swap(root_, tmp.root_);
  std::swap(nodes_, tmp.nodes_);

  return *this;
}

template <typename T>
ad_set::Tree<T> &ad_set::Tree<T>::operator =( Tree &&that )
{
  if (this == &that)
    return *this;

  Tree tmp{std::move(that)};
  std::swap(root_, tmp.root_);
  std::swap(nodes_, tmp.nodes_);

  return *this;
}

template <typename T>
typename ad_set::Tree<T>::iter_n_bool ad_set::Tree<T>::insert( const T &key )
{
  iter_n_bool pair{iterator{}, false};
  size_t old_size{nodes_.size()};

  root_ = Insert(root_, key, pair.first);

  if (nodes_.size() != old_size)
    pair.second = true;

  return pair;
}

template <typename T>
ad_set::Tree<T> &ad_set::Tree<T>::operator <<( const T &key )
{
  insert(key);

  return *this;
}

template <typename T>
typename ad_set::Tree<T>::iterator ad_set::Tree<T>::find( const T &key ) const
{
  lit found = detail::Find(root_, key);
  if (found == nulit)
    return end();
  return iterator{found};
}

template <typename T>
typename ad_set::Tree<T>::iterator ad_set::Tree<T>::lower_bound( const T &kmin ) const
{
  if (kmin == nodes_.begin()->key_)
    return begin();

  return FindLower(root_, kmin);
}

template <typename T>
typename ad_set::Tree<T>::iterator ad_set::Tree<T>::FindLower( lit nd, const T &key ) const
{
  if (nd == nulit)
    return iterator{};
  if (key < nd->key_)
  {
    if (nd->left_ == nulit)
      return iterator{nd};
    return FindLower(nd->left_, key);
  }
  if (key > nd->key_)
  {
    if (nd->right_ == nulit)
      return ++iterator{nd};
    return FindLower(nd->right_, key);
  }

  return iterator{nd};
}

template <typename T>
typename ad_set::Tree<T>::iterator ad_set::Tree<T>::begin( void ) const
{
  return iterator{nodes_.begin()};
}

template <typename T>
typename ad_set::Tree<T>::iterator ad_set::Tree<T>::end( void ) const
{
  return iterator{nodes_.end()};
}

template <typename T>
void ad_set::Tree<T>::erase( iterator it )
{
  erase(*it);
}

template <typename T>
void ad_set::Tree<T>::erase( const T &key )
{
  root_ = Delete(root_, key);
}

template <typename T>
void ad_set::Tree<T>::DotDump( const std::string &pngname /* = "dump.png" */,
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
  if (root_ != nulit)
    root_->RecDotPrint(fout);

  fout << "}\n";
  fout.close();

  std::string promt = "dot " + dotname + " -Tpng > " + pngname;
  system(promt.c_str());
}


template <typename T>
typename ad_set::Tree<T>::lit ad_set::Tree<T>::Insert( lit nd, const T &key, iterator &ins_it )
{
  if (nd == nulit)
  {
    // if tree is empty
    nodes_.push_back(detail::Node<T>{key});

    ins_it = iterator{nodes_.begin()};
    return nodes_.begin();
  }

  if (key < nd->key_)
  {
    if (nd->left_ == nulit)
    {
      nd->left_ = nodes_.insert(nd, detail::Node<T>{key});
      ins_it = iterator{nd->left_};
    }
    else
      nd->left_ = Insert(nd->left_, key, ins_it);
  }
  else if (key > nd->key_)
  {
    if (nd->right_ == nulit)
    {
      lit nxt{nd};
      nd->right_ = nodes_.insert(++nxt, detail::Node<T>{key});
    }
    else
      nd->right_ = Insert(nd->right_, key, ins_it);
  }
  else
  {
    ins_it = iterator(nd);
    return nd;
  }

  return detail::Balance<T>(nd);
}

template <typename T>
typename ad_set::Tree<T>::lit ad_set::Tree<T>::Delete( lit nd, const T &key )
{
  if (nd == nulit)
    return nulit;
  if (key < nd->key_)
    nd->left_ = Delete(nd->left_, key);
  else if (key > nd->key_)
    nd->right_ = Delete(nd->right_, key);
  else // key == nd->key_
  {
    auto left = nd->left_;
    auto right = nd->right_;
    auto parent = nd->parent_;

    // deleting node
    nodes_.erase(nd);

    if (right == nulit)
      return left;

    auto min = detail::FindMin(right);
    min->right_ = DelMin(right);
    min->left_ = left;
    min->parent_ = parent;

    return detail::Balance<T>(min);
  }

  return detail::Balance<T>(nd);
}

template <typename T>
typename ad_set::Tree<T>::lit ad_set::Tree<T>::CopyNd( lit nd, lit parent )
{
  if (nd == nulit)
    return nulit;

  lit new_root;

  if (nodes_.empty())
  {
    nodes_.push_front(nd->key_);
    new_root = nodes_.begin();
  }
  else
  {
    if (parent->key_ < nd->key_)
      ++parent;
    new_root = nodes_.insert(parent, nd->key_);
  }

  new_root->left_  = CopyNd(nd->left_, new_root);
  new_root->right_ = CopyNd(nd->right_, new_root);

  return new_root;
}
template <typename T>
std::istream &ad_set::operator >>( std::istream &ist, ad_set::Tree<T> &tr )
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
