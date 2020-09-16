#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <iterator>

template <typename type>
struct Node_elem
{
  type value;
  typename std::list<Node_elem<type>>::iterator Head;
};

template<typename type>
struct Freq_elem
{
  std::list<Node_elem<type>> Node_list;
  const size_t counter;

  Freq_elem( size_t counter = 0 ) : Node_list(),
                                    counter(counter)
  {}
};


template <typename type, typename key_type = unsigned long long>
class LFU_cache
{
private:
  size_t capacity_;

  // service struct for LFU algorith
  std::list<Freq_elem<type>> Freq_list_;

  using List_it = typename std::list<Freq_elem<type>>::iterator;
  using Hash_tbl = std::unordered_map<key_type, List_it>;
  //using Hash_it = typename Hash_tbl::iterator;

  Hash_tbl hash_table_;

public:

  // class constructor
  explicit LFU_cache( size_t capacity = 0 ) : capacity_(capacity),
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
      val_lst->second->counter++;
      return true;
    }
    // value is fully new to cache
    if (cache_.size() >= capacity_)
    {
      Emplace_(val, val_hash);
      return false;
    }

    cache_.push_front({val, 1});
    hash_table_[val_hash] = cache_.begin();

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

  void Emplace_( const type &value, key_t hash )
  {
    auto Min_lst = FindMin_();

    List_it lst_it = Min_lst->second;
    hash_table_.erase(Min_lst);
    hash_table_[hash] = lst_it;
    lst_it->counter = 1;
    lst_it->value = value;
  }

  auto FindMin_( void )
  {
    auto Min_lst = hash_table_.begin();

    for (auto it = hash_table_.begin(); it != hash_table_.end(); ++it)
    {
      if (it->second->counter < Min_lst->second->counter)
        Min_lst = it;
    }

    return Min_lst;
  }
};

template <typename type>
std::ostream & operator <<( std::ostream &ost, const LFU_cache<type> &lfu )
{
  int counter = 0;
  for (auto &ls : lfu.cache_)
  {
    ost << "Elem #" << counter++ << "\n{\n  value = " << ls.value;
    ost << "\n  counter = " << ls.counter << "\n}\n";
  }

  return ost;
}

#endif //CACHE_CACHE_H
