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

  // pointer to hash_func
  key_type (*hash_func)( const byte *bytes, size_t size );

  // service struct for LFU algorithm
  struct lst_elem
  {
    type value;
    size_t counter;
  };
  std::list<lst_elem> _cache;
  using List_it = typename std::list<type>::iterator;
  std::unordered_map<key_type, std::list<List_it>> hash_table;

public:

  // class constructor
  explicit LFU_cache( size_t capacity = 0 ) : _capacity(capacity),
                                              _cache(capacity)
  {
  }

  const type & find( const type &val )
  {

  }

  // class destructor
  ~LFU_cache( void )
  {

  }

private:

  template <typename T>
  static T hash( T val )
  {
    return val;
  }
};



#endif //CACHE_CACHE_H
