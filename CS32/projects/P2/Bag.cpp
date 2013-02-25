#include "Bag.h"
#include <iostream>

using namespace std;

Bag::Bag()
{
	m_head = NULL;
	m_tail = NULL;
} //constructor

Bag::~Bag()
{
	start(); //makes sure the head is at the beginning
	if (m_head) //if there are any resources allocated to the bag
	{
		while (m_head->m_next) //steps through and deletes 1 behind the step
		{
			m_head = m_head->m_next;
			delete m_head->m_prev;
		}
		delete m_head; //deletes the last step
	}
	//destructor
}

Bag::Bag(const Bag& a)
{
	Node* current = a.m_head;
	Node* prev = NULL;
	for (current; current != NULL; prev = current, current = current->m_next)
	{
		for (int i = 0; i < current->m_count; i++)
		{
			insert(current->m_item); //inserts the current item a number of times equal to its count
		}
		if (prev) //if there is a previous value, point to it
		{
			current->m_prev = prev;
			prev->m_next = current; //points back
		}
		else
		{
			current->m_prev = NULL;
			m_head = current;
		}
		m_tail = current; //the tail moves along with the last element until reaching the end
	}
//copy constructor
}

Bag& Bag::operator=(const Bag& a)
{
	if (m_head != a.m_head) //checks to make sure the bag being copied is a different list
	{
		//first clear the left side so it can be replaced
		if (m_head)
		{
			while (m_head->m_next) //steps through and deletes 1 behind the step
			{
				m_head = m_head->m_next;
				delete m_head->m_prev;
			}
		}
		delete m_head; //deletes the last step
		m_head = NULL;
		m_tail = NULL;


		Node* current = a.m_head;
		Node* prev = NULL;
		for (current; current != NULL; prev = current, current = current->m_next)
		{
			insert(current->m_item);
			int itemCount = current->m_count; //used to change the number of items to the count value
			Node* n = m_head;
			for (n; n->m_item != current->m_item; n = n->m_next) //finds the inserted item
				;
			n->m_count = itemCount; //changes it to match the number of items in the original.
		}
	}
	return *this;
}

bool Bag::empty() const
{
	if (m_head)
		return false;
	return true;
	//return true if bag is empty
}

int Bag::size() const
{
	int size = 0;
	Node* current = m_head;
	if (current)
		for (current; current != NULL; current = current->m_next)
			size += current->m_count; //increments by the # of items in each Node

	return size;
	//returns # of items in the bag
}

int Bag::uniqueSize() const
{
	int uniqueSize = 0;
	Node* current = m_head;
	if (current)
		for (current; current != NULL; current = current->m_next)
			uniqueSize++; //increments by 1 for each distinct item
	return uniqueSize;
	//returns # of distinct items in the bag
}

bool Bag::insert(const ItemType& value)
{
	if (m_head) //checks that there is at least one other item
	{
		Node* current = m_head;
		for (current; current->m_next != NULL && current->m_item != value; current = current->m_next)
			; //moving current to either the value to be incremented or the end of the list
		if (current->m_item == value) //if it found a matching value
		{
			current->m_count++; //increment
			return true;
		}
		if (!current->m_next) //if it didnt find a matching value
		{
			Node* newNode = new Node();
			current->m_next = newNode;
			newNode->m_count = 1; //first item to be added
			newNode->m_item = value;
			newNode->m_prev = current; //previous pointer points one item back
			newNode->m_next = NULL; // next pointer is NULL
			m_tail = newNode; //tail points to last element
			return true;
		}
	}
	else //current is null (no objects)
	{
		Node* newNode = new Node();
		m_head = newNode; //the brand new item
		m_tail = newNode;
		newNode->m_count = 1; //first item to be added
		newNode->m_item = value;
		newNode->m_prev = NULL; //previous pointer points one item back
		newNode->m_next = NULL; // next pointer is NULL
		return true;
	}
	return false; //something went wrong

	//inserts value into bag, returns false if failed
}

int Bag::erase(const ItemType& value)
{
	Node* current = m_head;

	for (current; current != NULL && current->m_item != value; current = current->m_next)
		; //tracks through the list until it finds the item
	if (current->m_count == 1) //if it found something and there is only one of it
	{
		if (m_head == m_tail) //if this is the last item
		{
			m_head = NULL;
			m_tail = NULL;
		}

		if (current->m_next && current->m_prev) //if both sides of the element are not null, connect them
		{ 
			current->m_prev->m_next = current->m_next;
			current->m_next->m_prev = current->m_prev;
		}

		Node* prev = current->m_prev; //2 new nodes for pointer housekeeping
		Node* next = current->m_next;

		delete current;

		if (!next) //pointer cleanup
		{
			if (prev)
			{
				m_tail = prev; //we deleted the final element
				m_tail->m_next = NULL; //sets the previous item's next pointer to NULL rather than have it point to a deleted object
			}
			else
				m_tail = NULL; // we deleted the only element
		}
		else if (!prev)
		{
			if (next)
			{
				m_head = next; //we deleted the first element
				m_head->m_prev = NULL; //sets the next item's prev pointer to NULL rather than have it point to a deleted object
			}
			else
				m_head = NULL; //we deleted the only element
		}
		return 1;
	}

	if (current->m_count > 1) //if it found something and there is more than one of it
	{
		current->m_count--; //decrement
		return 1;
	}

	return 0; //no items found
	//remove one instance of the item from the bag if present. if not, return 0
}

int Bag::eraseAll(const ItemType& value)
{
	Node* current = m_head;

	for (current; current != NULL && current->m_item != value; current = current->m_next)
		; //tracks through the list until it finds the item
	if (current != NULL) //if it found something
	{
		if (m_head == m_tail) //if this is the last item
		{
			m_head = NULL;
			m_tail = NULL;
		}

		if (current->m_next && current->m_prev) //if both sides of the element are not null, connect them
		{ 
			current->m_prev->m_next = current->m_next;
			current->m_next->m_prev = current->m_prev;
		}

		Node* prev = current->m_prev; //2 new nodes for pointer housekeeping
		Node* next = current->m_next;

		int itemsDeleted = current->m_count;
		delete current;
		if (!next)
		{
			if (prev)
			{
				m_tail = prev; //we deleted the final element
				m_tail->m_next = NULL; //sets the previous item's next pointer to NULL rather than have it point to a deleted object
			}
			else
				m_tail = NULL; // we deleted the only element
		}
		if (!prev)
		{
			if (next)
			{
				m_head = next; //we deleted the first element
				m_head->m_prev = NULL; //sets the next items's prev pointer to NULL rather than have it point to a deleted object
			}
			else
				m_head = NULL; //we deleted the only element
		}
	
		return itemsDeleted;
	}
	return 0; //didn't find anything
	//remove all instances of the item from the bag and return # removed
}

bool Bag::contains(const ItemType& value) const
{
	Node* current = m_head;
	for (current; current != NULL && current->m_item != value; current = current->m_next)
		; //tracks through the list until it finds the item
	if (current)
		return 1;
	return 0; //didnt find anything
}

int Bag::count(const ItemType& value) const
{
	Node* current = m_head;
	for (current; current != NULL && current->m_item != value; current = current->m_next)
		; //tracks through the list until it finds the item
	if (current)
		return current->m_count;
	return 0; //didnt find anything
}

void Bag::swap(Bag& other)
{
	Node* tempHead;
	Node* tempTail;
	tempHead = m_head; //assigns this into temp
	tempTail = m_tail;

	m_head = other.m_head; //assigns other to this
	m_tail = other.m_tail;

	other.m_head = tempHead; //assigns other to temp
	other.m_tail = tempTail;

}

void Bag::start()
{
	if (!m_head) //if the head pointer has gone off the end (pointing NULL), resets it to the tail
		m_head = m_tail;
	if (m_head) //if the tail pointer points to something, or if the original points to something
		while (m_head->m_prev) //if m_head is not pointing to the first element in the list, step it backwards until it does
			m_head = m_head->m_prev;
	//iteration function; points to the first element in the array/list
}

void Bag::next()
{
	m_head = m_head->m_next;
	//iteration function; points to the next element in the array/list
}

bool Bag::ended() const
{
	if (m_head)
		return false;
	return true;
	//returns true if end of iteration
}

const ItemType& Bag::currentValue() const
{
	return m_head->m_item;
	//the item in the current position in the iteration
}

int Bag::currentCount() const
{
	return m_head->m_count;
	//count of current position item
}


//Publicly implemented functions

void combine(Bag& b1, Bag& b2, Bag& result)
{
	for (result.start(); !result.ended();)
		result.eraseAll(result.currentValue()); //erases the current values in the result bag


	for (b1.start(); !b1.ended(); b1.next())
	{
		int i = 0;
		int j = b1.currentCount();
		for (i; i < j; i++)
			result.insert(b1.currentValue()); //inserts the item for each count it has
	}
	b1.start(); //resets the head pointer

	for (b2.start(); !b2.ended(); b2.next()) //repeat for the second bag
	{
		int i = 0;
		int j = b2.currentCount();
		for (i; i < j; i++)
			result.insert(b2.currentValue()); //inserts the item for each count it has
	}
	b2.start(); //resets the head pointer
	//When this function returns, result must contain a copy of all the items that appear in b1 or b2 or both, 
	//	and must not contain any other items.
} 

void subtract(Bag& b1, Bag& b2, Bag& result)
{
	for (result.start(); !result.ended();)
		result.eraseAll(result.currentValue()); //erases the current values in the result bag

	for (b1.start(); !b1.ended(); b1.next()) //start with the b1 bag and add all the values into the result bag
	{
		int i = 0;
		int j = b1.currentCount();
		for (i; i < j; i++)
			result.insert(b1.currentValue()); //inserts the item for each count it has
	}
	b1.start(); //resets the head pointer

	for (b2.start(); !b2.ended(); b2.next())
	{
		if (result.contains(b2.currentValue())) //if the bag contains any values from b2, erase them
		{
			int j;
			if (b2.count(b2.currentValue()) > result.count(b2.currentValue()))
				j = result.count(b2.currentValue()); //makes sure not to call the delete function more times than necessary 
			else
				j = b2.count(b2.currentValue());
			int i = 0;

			for (i; i < j; i++)
				result.erase(b2.currentValue()); //erases the item for each count it has in b2
		}
	}
	b2.start(); //resets the head pointer

	//If an item appears n1 times in b1 and n2 times in b2, then when this function returns, that item must appear 
	//	exactly n1−n2 times in result if n1 > n2; otherwise, it must not appear in result.
}

