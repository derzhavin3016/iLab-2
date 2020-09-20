#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <iterator>

#define OK(var) std::cout << "\n!!!OK" << var << "!!!\n";

template <typename type>
struct Freq_elem;


template <typename type>
using Freq_it = typename std::list<Freq_elem<type>>::iterator;

// structure which stored in node list
template <typename type>
struct Node_elem
{
  type value;
  Freq_it<type> Head;

  Node_elem( type val, Freq_it<type> head ) : value(val),
                                                     Head(head)
  {}
};

// structure which stored in freq list
template<typename type>
struct Freq_elem
{
  std::list<Node_elem<type>> Node_list;
  const size_t hits;

  Freq_elem( size_t hts ) : Node_list(),
                            hits(hts)
  {}
};
/* HOW IT WORKS:
 * FREQ_list --> [hits: 0] --> [hits: 1] --> ...
 *                  ^              ^
 *                  |              |
 *              Node_list       Node_list
 *                  ^              ^
 *                  |              |
 *                 [val:2]        [val:3]   -- request values
 * */

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
                                          hash_table_(),
                                          Freq_list_()
  {
  }
  /**
   * @brief Cache request function
   * @param val reference to request value
   * @return true if the hits has happened, false otherwise
   */
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
  } /* End of 'Request' function */

  /**
   * @brief Reload << operator to dump list via std::cout
   * @tparam tpe  - type of a LFU_cache template
   * @param ost - osrteam
   * @param lfu -LFU cache reference
   * @return reference to ostream (for multiple '<<')
   */
  template <typename tpe>
  friend std::ostream & operator <<( std::ostream &ost, const LFU_cache<tpe> &lfu );

  int Test( std::vector<int> &tests )
  {
    int hits = 0;

    for (auto &tst : tests)
      if (Request(tst))
        ++hits;

    return hits;
  } /* End of 'operator <<' function */

private:

  template <typename T>
  static T Hash_( T val )
  {
    return val;
  }

  /**
   * @brief Increment amount of hits in value function
   * @param n_it
   */
  void Increment_( Node_it n_it )
  {
#define DEL_IS_EM(old_it, new_it) \
    hash_table_.erase(n_it->value); \
    hash_table_[n_it->value] = (new_it)->Node_list.begin(); \
    (old_it)->Node_list.erase(n_it);   \
    if ((old_it)->Node_list.empty())         \
      Freq_list_.erase(old_it);


    Freq_it<type> n_head(n_it->Head);
    Freq_it<type> n_head_p1(++n_head);
    --n_head;

    if (n_head_p1 != Freq_list_.end() && n_head->hits + 1 == n_head_p1->hits)
    {
      n_head_p1->Node_list.push_front(Node_elem(n_it->value, n_head_p1));

      ReTie_(n_it, n_head, n_head_p1);
      return;
    }

    // add list with new hits amount
    Freq_it<type> new_head = Freq_list_.insert(n_head_p1, Freq_elem<type>(n_head->hits + 1));
    // push node to new freq list
    new_head->Node_list.push_front(Node_elem(n_it->value, new_head));
    ReTie_(n_it, n_head, new_head);


#undef DEL_IS_EM
  } /* End of 'Increment_' function */

  /**
   * @brief Retie a node function
   * @param node reference to node iterator for retie
   * @param src reference to iterator to element of Freq_list, where node is located
   * @param dst reference to iterator to element of Freq_list, where node will be located
   */
  void ReTie_( Node_it &node, Freq_it<type> &src, Freq_it<type> &dst )
  {
    hash_table_.erase(node->value);
    hash_table_[node->value] = dst->Node_list.begin();
    src->Node_list.erase(node);
    if (src->Node_list.empty())
      Freq_list_.erase(src);
  } /* End of 'ReTie_' function */

  /**
   * @brief Add new value to cache function
   * @param value
   */
  void AddCache_( type value )
  {
    if (hash_table_.size() >= capacity_)
      DelMin_();
    AddFreq_(value);

    hash_table_[value] = Freq_list_.front().Node_list.begin();
  } /* End of 'AddCache_' function */

  /**
   * @brief Delete least used node function
   */
  void DelMin_( void )
  {
    hash_table_.erase(Freq_list_.front().Node_list.front().value);
    Freq_list_.front().Node_list.pop_front();

    if (Freq_list_.front().Node_list.empty())
      Freq_list_.pop_front();
  } /* End of 'DelMin_' function*/

  /**
   * @brief Add new Frequency to Freq_list function
   * @param value
   */
  void AddFreq_( type value )
  {
    if (Freq_list_.empty() || Freq_list_.front().hits != 0)
      Freq_list_.push_front(Freq_elem<type>(0));

    Freq_list_.front().Node_list.push_front(Node_elem(value, Freq_list_.begin()));
  } /* End of 'AddFreq_' function */
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
