//Implemetation for the bag class

#include "Bag.h"
using namespace std;


Bag::Bag()
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
		m_bag[i].count = 0;
	//initializer for the bag object
}

bool Bag::empty() const
{
	//if the bag is empty, this function returns true
	if (m_bag[0].count == 0) //1st count has no value
		return true;
	return false;
}

int Bag::size() const
{
	int totalItems = 0;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
		totalItems += m_bag[i].count;
	return totalItems;
	//returns the number of items in the bag
}

int Bag::uniqueSize() const
{
	int totalUniqueItems = 0;
	for (int i = 0; i < DEFAULT_MAX_ITEMS && m_bag[i].count != 0; i++) 
		totalUniqueItems++;
	return totalUniqueItems;
	//returns the number of unique items in the bag
}

bool Bag::insert(const ItemType& value)
{
	//inserts a value into the bag, returns true if success
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (m_bag[i].item == value) //if the value to be added matches an item already in the bag, just increment the count
		{
			m_bag[i].count++;
			return true;
		}
		else if (m_bag[i].count == 0) //if the value doesn't match, create a new element with count 1
		{
			m_bag[i].item = value;
			m_bag[i].count++;
			return true;
		}
	}
	return false;	//if loop reaches the end of the array, no room left in bag
}

int Bag::erase(const ItemType& value)
{
	for (start(); !ended(); next())
	{
		if (m_bag[m_finger].item == value)
		{
			m_bag[m_finger].count--; //decrements the count by 1
			if (m_bag[m_finger].count == 0) //if this takes the count to 0, remove the entry and shift the array over
			{
				do //shifts the elements over
				{
					m_bag[m_finger].item = m_bag[m_finger+1].item;
					m_bag[m_finger].count = m_bag[m_finger+1].count;
					next();
				} while (!ended());
			}
			return 1;
		}
	}
	return 0;
}

int Bag::eraseAll(const ItemType& value)
{
	for (start(); !ended(); next())
	{
		if (m_bag[m_finger].item == value)
		{
			int numberErased = m_bag[m_finger].count; //logs the # of elements erased first
			do //shifts the elements over to fill the "hole."
			{
				m_bag[m_finger].item = m_bag[m_finger+1].item;
				m_bag[m_finger].count = m_bag[m_finger+1].count;
				next();
			} while (!ended());
			return numberErased;
		}
	}
	return 0; //no matches
}

bool Bag::contains(const ItemType& value) const
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS && m_bag[i].count != 0; i++) //checks every item
	{
		if (m_bag[i].item == value)
			return true;
	}
	return false;
}

int Bag::count(const ItemType& value) const
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		if (m_bag[i].item == value) //if the element is found, return the count
			return m_bag[i].count;
	}
	return 0; //no matches
}

void Bag::swap(Bag& other)
{
	//exchanges the contents of the bag with the contents of another bag
	Bag temp; //temp bag to hold transfers
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		temp.m_bag[i] = m_bag[i]; //loads first bag element into temp
		m_bag[i] = other.m_bag[i]; //loads second bag element into first
		other.m_bag[i] = temp.m_bag[i]; //loads temp bag element into second
	}
}

void Bag::start()
{
	m_finger = 0;
}

void Bag::next()
{
	m_finger++;
}

bool Bag::ended()
{
	if (m_bag[m_finger].count == 0) //checks if the current item in the bag array exists
		return true;
	return false;
}

const ItemType& Bag::currentValue() //returns a reference to the current item being pointed
{
	ItemType& bag = m_bag[m_finger].item;
	return bag;
}

int Bag::currentCount()
{
	int c = m_bag[m_finger].count;
	return c;
}



