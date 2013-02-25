#include "newBag.h"
#include <iostream>
using namespace std;

Bag& Bag::operator=(const Bag& a)
{
	if (this != &a)
	{
		delete [] m_bag; //cleanup left side
		m_bagElements = a.m_bagElements; //copies # of elements from right to left
		m_bag = new BagItem[m_bagElements]; //creates a new array to hold old elements
		for (int i = 0; i < m_bagElements; i++) //copies over a into the new array
			m_bag[i] = a.m_bag[i];
	}
	return *this;
}

Bag::Bag(int size)
{
	if (size < 0)
	{
		cout << "Bag cannot have a negative size!" << endl;
		exit(0);
	}
	m_bagElements = size;
	m_bag = new BagItem[size];
	for (int i = 0; i < size; i++)
		m_bag[i].count = 0;
}

Bag::Bag(const Bag&)
{
	m_bag = new BagItem[m_bagElements];
	//copy constructor
}

Bag::~Bag()
{
	delete [] m_bag; //removes m_bag's resources
	m_bagElements = 0;
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
	for (int i = 0; i < m_bagElements; i++)
		totalItems += m_bag[i].count;
	return totalItems;
	//returns the number of items in the bag
}

int Bag::uniqueSize() const
{
	int totalUniqueItems = 0;
	for (int i = 0; i < m_bagElements && m_bag[i].count != 0; i++) 
		totalUniqueItems++;
	return totalUniqueItems;
	//returns the number of unique items in the bag
}

bool Bag::insert(const ItemType& value)
{
	//inserts a value into the bag, returns true if success
	for (int i = 0; i < m_bagElements; i++)
	{
		if (m_bag[i].item == value) //if the value to be added matches an item already in the bag, just increment the count
		{
			m_bag[i].count++;
			return true;
		}
	}

	for (int j = 0; j < m_bagElements; j++)
	{
		if (m_bag[j].count == 0) //if the value doesn't match, create a new element with count 1
		{
			m_bag[j].item = value;
			m_bag[j].count++;
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
	for (int i = 0; i < m_bagElements && m_bag[i].count != 0; i++) //checks every item
	{
		if (m_bag[i].item == value)
			return true;
	}
	return false;
}

int Bag::count(const ItemType& value) const
{
	for (int i = 0; i < m_bagElements; i++)
	{
		if (m_bag[i].item == value) //if the element is found, return the count
			return m_bag[i].count;
	}
	return 0; //no matches
}

void Bag::swap(Bag& other)
{
	//exchanges the contents of the bag with the contents of another bag
	/*Bag temp; //temp bag to hold transfers
	temp.m_bag = this->m_bag;  //loads first bag element into temp
	temp.m_bagElements = this->m_bagElements;
	this->m_bag = other.m_bag;//loads second bag element into first
	this->m_bagElements = other.m_bagElements;
	other.m_bag = temp.m_bag; //loads temp bag element into second
	other.m_bagElements = temp.m_bagElements; */
	Bag temp;
	temp = *this;
	*this = other;
	other = temp;
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

