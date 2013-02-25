#ifndef MYHASHMAP_INCLUDED
#define MYHASHMAP_INCLUDED

const int DEFAULT_NUM_BUCKETS = 1000000;

#include <map>  // YOU MUST NOT USE THIS HEADER
#include <string>

// In accordance with the spec, YOU MUST RE-IMPLEMENT THIS CLASS, since
// you are not allowed to use an STL map or unordered_map or hash_map.

template <typename ValueType>
class MyHashMap
{
public:

    MyHashMap(int numBuckets = DEFAULT_NUM_BUCKETS)
     : m_curr(m_map.begin())
    {}

    ~MyHashMap()
    {
    }

    void associate(std::string key, const ValueType& value)
    {
		transform(key.begin(), key.end(), key.begin(), tolower);
		//only associate lower case words, makes things easier later
        m_map[key] = value;
    }

    const ValueType* find(std::string key) const
    {
        typename HelperMapType::const_iterator it = m_map.find(key);
        if (it == m_map.end())
            return NULL;
        else
            return &it->second;
    }

    ValueType* find(std::string key)
    {
          // Do not change the implementation of this overload of find
        const MyHashMap<ValueType>* constThis = this;
        return const_cast<ValueType*>(constThis->find(key));
    }

    ValueType* getFirst(std::string& key)
    {
        m_curr = m_map.begin();
        if (m_curr == m_map.end())
            return NULL;

        key = m_curr->first;
        return &m_curr->second;
    }

    ValueType* getNext(std::string& key)
    {
        m_curr++;
        if (m_curr == m_map.end())
            return NULL;

        key = m_curr->first;
        return &m_curr->second;
    }

    int numItems() const
    {
        return m_map.size();
    }

private:
      // YOU ARE NOT ALLOWED TO USE AN STL MAP IN YOUR SOLUTION
    typedef std::map<std::string, ValueType> HelperMapType;
    HelperMapType                    m_map;
    typename HelperMapType::iterator m_curr;
};

#endif // MYHASHMAP_INCLUDED
