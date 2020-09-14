#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H

#include <unordered_map>
#include <list>
#include <iterator>

template<typename type>
struct lst_elem
{
  type value;
  size_t counter;

  lst_elem( type value = 0, size_t counter = 0 ) : value(value),
                                                   counter(counter)
  {}
};


template <typename type, typename key_type = unsigned long long>
class LFU_cache
{
private:
  size_t _capacity;

  // service struct for LFU algorith
  std::list<lst_elem<type>> _cache;

  using List_it = typename std::list<lst_elem<type>>::iterator;
  using Hash_tbl = std::unordered_map<key_type, List_it>;
  using Hash_it = typename Hash_tbl::iterator;

  Hash_tbl _hash_table;

public:

  // class constructor
  explicit LFU_cache( size_t capacity = 0 ) : _capacity(capacity),
                                              _cache(),
                                              _hash_table()
  {
  }

  bool Request( const type &val )
  {
    // get a hash
    key_t val_hash = _Hash(val);
    // find in map by hash value
    auto val_lst = _hash_table.find(val_hash);

    if (val_lst != _hash_table.end())
    {
      // this hash exist
      val_lst->second->counter++;
      return true;
    }
    // value is fully new to cache
    if (_cache.size() >= _capacity)
    {
      _Emplace(val, val_hash);
      return false;
    }

    _cache.push_front({val, 1});
    _hash_table[val_hash] = _cache.begin();

    return false;
  }
  template <typename tpe>
  friend std::ostream & operator <<( std::ostream &ost, const LFU_cache<tpe> &lfu );


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

  void _Emplace( const type &value, key_t hash )
  {
    auto Min_lst = _FindMin();

    List_it lst_it = Min_lst->second;
    _hash_table.erase(Min_lst);
    _hash_table[hash] = lst_it;
    lst_it->counter = 1;
    lst_it->value = value;
  }

  auto _FindMin( void )
  {
    auto Min_lst = _hash_table.begin();

    for (auto it = _hash_table.begin(); it != _hash_table.end(); ++it)
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
  for (auto &ls : lfu._cache)
  {
    ost << "Elem #" << counter++ << "\n{\n  value = " << ls.value;
    ost << "\n  counter = " << ls.counter << "\n}\n";
  }

  return ost;
}

#endif //CACHE_CACHE_H
