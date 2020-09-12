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

    auto val_lst = _hash_table.find(val_hash);
    if (val_lst != _hash_table.end())
    {
      auto val_cache = _CacheFind(val, val_lst);
      if (val_cache != val_lst->end())
      {
        val_cache->counter++;
        return val_cache->value;
      }

      val_lst->push_back(_CacheAdd(val, val_hash));
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

  void _CacheAdd( const type &val, key_t hash )
  {


  }

  List_it _FindMin( void )
  {
    size_t min = _hash_table.begin()->beign()->counter;
    List_it it_min = _hash_table.begin()->beign();

    for (auto &mp : _hash_table)
      for (auto &lst : mp)
      {
        if (lst->counter < min)
          min =
      }
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
