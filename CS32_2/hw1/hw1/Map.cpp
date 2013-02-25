#include <iostream>
#include <string>
#include "Map.h"


Map::Map()
{
	m_size = 0;
	//we leave the array uninitialized because we will only access
	//elements up to the tracked size of the array
}

bool Map::empty() const
{
	return (m_size == 0);
}

int Map::size() const
{
	return m_size; 
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (size() == DEFAULT_MAX_ITEMS || contains(key))
		return false; //does not perform the insert if no room or if 
					  //the key already exists in the array

	//create a new Pair and insert it into the array; increment size
	Pair p;
	p.m_key = key;
	p.m_value = value;

	m_items[m_size] = p;
	m_size++;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	if (!contains(key))
		return false; //the inputted key is not in the array

	for (int i = 0; i < m_size; i++)
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
	for (int i = 0; i < m_size; i++)
	{
		if (m_items[i].m_key == key) //this isnt portable; can't change between other key types
		{	//if the key matches a key at the current array pos
			m_size--;
			for (i; i < m_size; i++)
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
	for (int i = 0; i < m_size; i++)
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
		for (int i = 0; i < m_size; i++)
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
	int smallerSize, remainder;
	bool otherIsLarger;
	if (m_size < other.m_size)
	{
		smallerSize = m_size;
		remainder = other.m_size - smallerSize;
		otherIsLarger = true; //other is larger, ldo
	}	
	else
	{
		smallerSize = other.m_size;
		remainder = m_size - smallerSize;
		otherIsLarger = false; //other is smaller
	}
	//we need this so we don't accidentally copy undefined array elements
	
	int x;
	Pair p;

	//swaps overlapping item arrays
	for (x = 0; x < smallerSize; x++)
	{	//swap each individual item
		p = m_items[x];
		m_items[x] = other.m_items[x];
		other.m_items[x] = p;
	}
	 //now we need to copy over the non-overlapping elements
	if (otherIsLarger) //other is larger, need to copy extras to this
	{	
		for (x; x < other.size(); x++)
		{
			p = other.m_items[x];
			m_items[x] = p;
		}
		other.m_size -= remainder;
		m_size += remainder; //modifies the sizes to reflect the changes
	}
	else // other is smaller, need to copy extras over to it
	{
		for (x; x < size(); x++)
		{
			p = m_items[x];
			other.m_items[x] = p;
		}
		m_size -= remainder;
		other.m_size += remainder; //modifies the sizes to reflect changes
	}
}

