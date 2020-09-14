#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H

#include <unordered_map>
#include <list>
#include <iterator>

typedef unsigned char byte;


template <typename type, typename key_type = unsigned long long>
class LFU_cache
{
private:
  size_t _capacity;

  // service struct for LFU algorithm
  struct lst_elem
  {
    type value;
    size_t counter;
  };
  std::list<lst_elem> _cache;

  using List_it = typename std::list<type>::iterator;
  using Hash_tbl = std::unordered_map<key_type, std::list<List_it>>;
  using Map_it = typename Hash_tbl::iterator;
  using Map_lst_it = typename std::list<List_it>::iterator;
  Hash_tbl _hash_table;

public:

  // class constructor
  explicit LFU_cache( size_t capacity = 0 ) : _capacity(capacity),
                                              _cache(capacity)
  {
  }

  const type & Request( const type &val )
  {
    // get a hash
    key_t val_hash = _Hash(val) % _capacity;

    // find in map by hash value
    auto val_lst = _hash_table.find(val_hash);
    if (val_lst != _hash_table.end())
    {
      // list with this hash exist
      auto val_cache = _CacheFind(val, val_lst);
      if (val_cache != val_lst->end())
      {
        // this value exist in cache
        val_cache->counter++;
        return val_cache->value;
      }
      // value doesn't exist in list, but it's hash exist

      if (_cache.size() >= _capacity)
      {
        auto Min_lst = _FindMin();
        Min_lst->counter = 1;
        Min_lst->value = val;
        return val;
      }

      _cache.push_back(lst_elem{val, 1});
      val_lst->push_back(_cache.back());

      return val;
    }
    // value is fully new to cache
    if (_cache.size() >= _capacity)
    {
      auto Min_lst = _FindMin();
      Min_lst->counter = 1;
      Min_lst->value = val;
      Min_lst
      return val;
    }
    _hash_table.insert(val_hash, std::list<List_it>{_CacheAdd(val, val_hash)});
  }

  // class destructor
  ~LFU_cache( void )
  {

  }

private:

  template <typename T>
  static T _Hash( T val )
  {
    return val;
  }

  Map_lst_it _CacheAdd( const type &val, bool IsNew )
  {
    if (_cache.size() >= _capacity)
      auto Min_lst = _FindMin();

  }

  Map_lst_it _FindMin( void )
  {
    auto Min_lst = _hash_table.begin()->begin();

    for (auto &mp : _hash_table)
      for (auto &lst : mp)
      {
        if (lst->counter < Min_lst->counter)
          Min_lst = lst;
      }

    return Min_lst;
  }
  List_it _CacheFind( const type &value, const Map_it & mit )
  {
    for (auto &lst : *mit)
      if (lst->value == value)
        return lst;

    return mit->end();
  }
};



#endif //CACHE_CACHE_H
