#include <iostream>
#include "newMap.h"


Map::Map() : m_size_max(DEFAULT_MAX_ITEMS), m_size_used(0)
{
	m_items = new Pair[DEFAULT_MAX_ITEMS];
}

Map::Map(int n) : m_size_max(n), m_size_used(0)
{
	if (n < 0)
	{
		std::cout << "Fatal error: array has too few elements. Exiting.\n";
		exit(0);
	} 
	m_items = new Pair[n];
	//we leave the array uninitialized because we will only access
	//elements up to the tracked size of the array
}

Map::~Map()
{
	delete [] m_items;
}

Map::Map(const Map& src)
{
	m_size_used = src.m_size_used;
	m_size_max = src.m_size_max;
	m_items = new Pair[m_size_max];

	//copies over all the pairs from the src
	for(int i = 0; i < m_size_used; i++)
		m_items[i] = src.m_items[i];
}

Map& Map::operator=(const Map& src)
{
	if (m_items == src.m_items)
		return (*this); //prevents aliasing

	m_size_max = src.m_size_max;
	m_size_used = src.m_size_used;

	//need to resize the array, so better to just delete and make again
	delete [] m_items;
	m_items = new Pair[m_size_max];
	//copies over all the pairs from src
	for(int i = 0; i < m_size_used; i++)
		m_items[i] = src.m_items[i];
	
	return (*this);
}

bool Map::empty() const
{
	return (m_size_used == 0);
}

int Map::size() const
{
	return m_size_used; 
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (size() == m_size_max || contains(key))
		return false; //does not perform the insert if no room or if 
					  //the key already exists in the array

	//create a new Pair and insert it into the array; increment size
	Pair p;
	p.m_key = key;
	p.m_value = value;

	m_items[m_size_used] = p;
	m_size_used++;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	if (!contains(key))
		return false; //the inputted key is not in the array

	for (int i = 0; i < m_size_used; i++)
	{
		if (m_items[i].m_key == key) 
		{	//if the key matches a key at the current array pos
			m_items[i].m_value = value; //change the value and return
			return true;
		}
	}
	return false; //if it somehow made it here there was an error with contains()

}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (contains(key))
		return update(key, value);
	else
		return insert(key, value);
}

bool Map::erase(const KeyType& key)
{
	if (empty())	return false;
	for (int i = 0; i < m_size_used; i++)
	{
		if (m_items[i].m_key == key) //this isnt portable; can't change between other key types
		{	//if the key matches a key at the current array pos
			m_size_used--;
			for (i; i < m_size_used; i++)
			{
				m_items[i] = m_items[i+1];
			}
			return true;
		}
	}
	return false; //didnt find the key
}

bool Map::contains(const KeyType& key) const
{
	for (int i = 0; i < m_size_used; i++)
	{
		if (m_items[i].m_key == key) 
		{	//if the key matches a key at the current array pos
			return true;
		}
	}
	return false; //didn't find it
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	if (contains(key))
	{
		for (int i = 0; i < m_size_used; i++)
		{
			if (m_items[i].m_key == key) 
			{	//if the key matches a key at the current array pos
				value = m_items[i].m_value; //change the value and return
				return true;
			}
		}
	}
	return false;
}	

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i < 0 || i >= size())
		return false; //invalid parameters

	key = m_items[i].m_key;
	value = m_items[i].m_value;
	return true;
}

void Map::swap(Map& other)
{
	//swap integers first
	int sizeUsedHolder = m_size_used;
	m_size_used = other.m_size_used;
	other.m_size_used = sizeUsedHolder;

	int sizeMaxHolder = m_size_max;
	m_size_max = other.m_size_max;
	other.m_size_max = sizeMaxHolder;

	//swap pointers instead of swapping arrays
	Pair* p = m_items;
	m_items = other.m_items;
	other.m_items = p;
}

