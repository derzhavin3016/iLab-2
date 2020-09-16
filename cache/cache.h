#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <iterator>

#define OK std::cout << "\n!!!OK!!!\n";

template <typename type>
struct Freq_elem;

template <typename type>
using Freq_it = typename std::list<Freq_elem<type>>::iterator;

template <typename type>
struct Node_elem
{
  type value;
  Freq_it<type> Head;

  Node_elem( type val, const Freq_it<type> &head ) : value(val),
                                                     Head(head)
  {}

  Node_elem( const Node_elem &n_elem ) : value(n_elem.value),
                                         Head(n_elem.Head)
  {}
};

template<typename type>
struct Freq_elem
{
  std::list<Node_elem<type>> Node_list;
  const size_t hits;

  Freq_elem( size_t hts ) : Node_list(),
                            hits(hts)
  {}
};


template <typename type, typename key_type = unsigned long long>
class LFU_cache
{
private:
  size_t capacity_;

  // service struct for LFU algorithm
  std::list<Freq_elem<type>> Freq_list_;

  using Node_it = typename std::list<Node_elem<type>>::iterator;
  using Hash_tbl = std::unordered_map<key_type, Node_it>;
  using Hash_it = typename Hash_tbl::iterator;

  Hash_tbl hash_table_;

public:

  // class constructor
  explicit LFU_cache( size_t capacity ) : capacity_(capacity),
                                              hash_table_()
  {
  }

  bool Request( const type &val )
  {
    // get a hash
    key_t val_hash = Hash_(val);
    // find in map by hash value
    auto val_lst = hash_table_.find(val_hash);

    if (val_lst != hash_table_.end())
    {
      // this hash exist
      Increment_(val_lst->second);
      return true;
    }
    // value is fully new to cache
    AddCache_(val);
    return false;
  }
  template <typename tpe>
  friend std::ostream & operator <<( std::ostream &ost, const LFU_cache<tpe> &lfu );

  int Test( std::vector<int> &tests )
  {
    int hits = 0;

    for (auto &tst : tests)
      if (Request(tst))
        ++hits;

    return hits;
  }

  // class destructor
  ~LFU_cache( void )
  {
  }

private:

  template <typename T>
  static T Hash_( T val )
  {
    return val;
  }

  void Increment_( Node_it &n_it )
  {
#define DEL_IS_EM(var) \
    if ((var)->Node_list.empty()) \
      Freq_list_.erase((var));

    Freq_it<type> n_head = n_it->Head;

    if (n_it->Head->hits + 1 == (++n_head)->hits)
    {
      n_head->Node_list.push_front(Node_elem(n_it->value, n_head));
      (--n_head)->Node_list.erase(n_it);
      DEL_IS_EM(n_head);
      return;
    }
    // add list with new hits amount
    Freq_it<type> new_head = Freq_list_.insert(n_it->Head, Freq_elem<type>((--n_head)->hits + 1));
    // push node to new freq list
    new_head->Node_list.push_front(Node_elem(n_it->value, new_head));
    (--new_head)->Node_list.erase(n_it);
    DEL_IS_EM(new_head);

#undef DEL_IS_EM
  }


  void AddCache_( type value )
  {
    if (hash_table_.size() >= capacity_)
      DelMin_();
    AddFreq_(value);

    hash_table_[value] = Freq_list_.front().Node_list.begin();
  }

  void DelMin_( void )
  {
    hash_table_.erase(Freq_list_.front().Node_list.front().value);
    Freq_list_.front().Node_list.pop_front();


    if (Freq_list_.front().Node_list.empty())
      Freq_list_.pop_front();
  }

  void AddFreq_( type value )
  {
    if (Freq_list_.front().hits != 1)
      Freq_list_.push_front(Freq_elem<type>(1));

    Freq_list_.front().Node_list.push_front(Node_elem(value, Freq_list_.begin()));
  }
};

template <typename type>
std::ostream & operator <<( std::ostream &ost, const LFU_cache<type> &lfu )
{
  int counter = 0;
  for (auto &lf : lfu.Freq_list_)
  {
    for (auto &ln : lf.Node_list)
    {
      ost << "Elem #" << counter++ << "\n{\n  value = " << ln.value;
      ost << "\n  hits = " << lf.hits << "\n}\n";
    }
  }

  return ost;
}

#endif //CACHE_CACHE_H
