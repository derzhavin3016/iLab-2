#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H

#include <unordered_map>
#include <list>
#include <iterator>

template <typename type, typename key_type = unsigned long long>
class LFU_cache
{
private:
  size_t _size;
  struct list_elem
  {
    type elem;
    size_t counter;

    list_elem( void ) : elem(), counter(0)
    {}
  };
  std::list<list_elem> _cache;
  std::unordered_map<key_type, typename std::list<list_elem>::iterator> hash_table;
public:

  // class constructor
  LFU_cache( void )
  {

  }

  // class destructor
  ~LFU_cache( void )
  {

  }
};

#endif //CACHE_CACHE_H
