class LRUCache{
public:
    LRUCache(int capacity) : m_capacity(capacity){
        
    }
    
    int get(int key) {
        if (m_hashmap.count(key)==0) {
            return -1;
        } else {
            ListIterator iter = m_hashmap[key];
            KeyValuePair pair = *iter;
            m_cache_item_list.erase(iter);
            m_cache_item_list.push_front(pair);
            m_hashmap[key] = m_cache_item_list.begin();
            return pair.second;
        }
    }
    
    void set(int key, int value) {
        if (m_hashmap.count(key)!=0) {
            m_cache_item_list.erase(m_hashmap[key]);
        }
        m_cache_item_list.push_front(KeyValuePair(key,value));
        m_hashmap[key] = m_cache_item_list.begin();
        if (m_cache_item_list.size() > m_capacity) {
            m_hashmap.erase(m_cache_item_list.back().first);
            m_cache_item_list.pop_back();
        }
    }
private:
    int m_capacity;
    typedef std::pair<int,int> KeyValuePair;
    std::list<KeyValuePair> m_cache_item_list;
    typedef std::list<KeyValuePair>::iterator ListIterator;
    unordered_map<int,ListIterator> m_hashmap; //<key,ListIterator>
};
