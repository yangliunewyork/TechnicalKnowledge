#include <iostream>
#include <cassert>
#include <unordered_map>
#include <list>
#include <memory>

template <typename KeyType, typename ValueType>
class LRU {
private:
  
  struct ListItem {
    ListItem(KeyType key, ValueType value) : m_key(key), m_value(value){}
    
    KeyType m_key;
    ValueType m_value;
  };
  typedef std::shared_ptr<ListItem> ListItemPtr;
  typedef std::list<ListItemPtr> LruList;
  typedef typename std::list<ListItemPtr>::iterator LruListPos;
  typedef std::unordered_map<KeyType, LruListPos> LruMapper;
  
public:
  LRU(std::size_t capacity) : m_capacity(capacity) {
    SetDefaultValue(ValueType());
  }

  void SetDefaultValue(ValueType val) {
    m_default_value = val;
  }
ValueType Get(KeyType key) {
    if (m_mapper.count(key) == 0) {
      return m_default_value;
    } else {
      // copy and swap
      LruListPos pos = m_mapper[key];
      const ListItemPtr & cur_item_ptr = *pos;
      m_list.push_front(cur_item_ptr);
      m_mapper[key] = m_list.begin();

      // erase 
      m_list.erase(pos);
      
      return m_list.front()->m_value;
    }
  }
  
  void Set(KeyType key, ValueType value) {
    if (m_mapper.count(key) != 0) {
      ValueType cc = Get(key);
      m_list.front()->m_value = value;
    } else {
      if (m_list.size() == m_capacity) {
        KeyType delete_key = m_list.back()->m_key;
        m_list.pop_back();
        m_mapper.erase(delete_key);
      }

      m_list.push_front(std::make_shared<ListItem>(key,value));
      m_mapper[key] = m_list.begin();
    }
  }
private:
  ValueType m_default_value;
  std::size_t m_capacity;
  LruList m_list;
  LruMapper m_mapper;
};



void UnitTest() {
  LRU<int,int> cache(2);
  cache.SetDefaultValue(-1);
  cache.Set(1,1);
  cache.Set(2,2);
  cache.Set(3,3);

  assert(cache.Get(1) == -1);
  
}

int main() {
  UnitTest();
  return 0;
}
