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
  std::list<type> _cache;

  // service struct for LFU algorithm
  struct map_elem
  {
    typename std::list<type>::iterator list_it;
    size_t counter;
  };

  std::unordered_map<key_type, map_elem> hash_table;
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
