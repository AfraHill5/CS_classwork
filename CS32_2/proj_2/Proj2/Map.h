#ifndef MAP_H
#define MAP_H

#include <string>

typedef std::string		KeyType;
typedef double			ValueType;

class Map
{
  public:
    Map();
	~Map();
	Map(const Map& src); //copy constructor
	Map& operator=(const Map& src); //overloaded = operator

    bool empty() const;
    int  size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);

private:
	struct Node //holds the data for one entry in the Map linked list
	{
		KeyType		k;
		ValueType	v;
		Node*		prev;
		Node*		next;
	};
	
	Node*	m_head; //points at the first value in the list
	Node*	m_tail; //points to the last value in the list
	int		m_count; //stores the amount of elements in the list
};

#endif