#include "Map.h"

using namespace std;


//Map implementations
Map::Map()
{
	m_head = NULL;
	m_tail = NULL;
	m_count = 0;
}

Map::~Map()
{	//need to clear the dynamically allocated memory holding Nodes
	while (m_head != NULL) //until we reach the end
	{
		Node* next = m_head->next;
		delete m_head;
		m_head = next;
	}
}

Map::Map(const Map& src) //copy constructor
{	
	Node* curr_src = src.m_head; //points to the first value of src
	Node* prev = NULL; //used later

	m_count = 0;

	while (curr_src != NULL) 
	{
		Node* a = new Node;
		a->k = curr_src->k;
		a->v = curr_src->v; //copy the key/value
		a->next = NULL;

		a->prev = prev; //tracks the previous node in the list
		if (prev != NULL)
			a->prev->next = a; //goes to previous node and inserts this as the "next"
		
		m_count++;

		if (m_count == 1) //this must be the first item if count ==1
			m_head = a;
		if (m_count == src.m_count) //this must be the last item
			m_tail = a;

		prev = a; //sets prev to this node so we can track it when we make the next one
		curr_src = curr_src->next;
	}
}
	
Map& Map::operator=(const Map& src) //overloaded = operator
{
	if (src.m_head == m_head)
		return (*this); //aliasing check

	Node* curr_src = src.m_head;
	
	//erase all of this list
	while (m_head != NULL)
	{
		Node* next = m_head->next;
		delete m_head;
		m_head = next;
	}

	m_tail = NULL;
	m_count = 0;

	while (curr_src != NULL)
	{
		insert(curr_src->k, curr_src->v); //inserts a new Node with src's current values
		curr_src = curr_src->next;
	}
	return (*this);
}


bool Map::empty() const
{
	return (m_count == 0);
}

int Map::size() const
{
	return (m_count);
}
bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (contains(key)) //if the key is present already
		return false; //can't have 2 of the same key in the map

	Node* A = new Node;
	A->k = key;
	A->v = value;
	A->next = NULL;


	if (empty()) //very easy to implement if the list is empty, so I check for it
	{
		A->prev = NULL;
		m_head = A;
		m_tail = A;
		m_count++;
		return true;
	}
	//else, the list has some elements in it
	A->prev = m_tail;
	if (m_tail != NULL)
		m_tail->next = A;

	m_tail = A; //we are adding it at the end
	
	m_count++;
	return true;
}
bool Map::update(const KeyType& key, const ValueType& value)
{
	Node* curr = m_head;
	while (curr != NULL)
	{
		if (curr->k == key) //if the key is found
		{
			curr->v = value;
			return true;
		}
		curr = curr->next;
	}
	return false; //didnt find the key
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (!(insert(key, value))) //if the update function fails
		update(key, value); //run the insert function
	return true;
	//this function never returns false because there is no
	//size limit for the map
}

bool Map::erase(const KeyType& key)
{
	if (!contains(key)) //if the item isn't in the list
		return false;

	Node* curr = m_head;
	while (curr->k != key) //tracks until it reaches the Node to be deleted
		curr = curr->next;

	Node* p = curr->prev;
	Node* n = curr->next; //keeps track of what curr was pointing to

	delete curr;

	if (p == NULL) //this means it was the first item in the list
		m_head = n; //adjust m_head to compensate for this
	else //if it was not the first item, adjust the pointers
		p->next = n;

	if (n == NULL) //if it was the last item in the list
		m_tail = p; //adjust the tail to compensate
	else //it was not the last item, so adjust the pointers
		n->prev = p;

	m_count--;
	return true;
}

bool Map::contains(const KeyType& key) const
{
	Node* curr = m_head;
	while (curr != NULL)
	{
		if (curr->k == key) //found the key in the list
			return true;
		curr = curr->next;
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	Node* curr = m_head;
	while (curr != NULL)
	{
		if (key == curr->k) //if there is a key match
		{
			value = curr->v;
			return true;
		}
		curr = curr->next;
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i < 0 || i >= size())
		return false; //i is invalid

	Node* curr = m_head;
	for (int x = 0; x < i; x++) //loops i times
		curr = curr->next;

	key = curr->k;
	value = curr->v;
	return true;
}

void Map::swap(Map& other)
{
	//swap the counts
	int temp = other.m_count;
	other.m_count = m_count;
	m_count = temp;

	//swap the head ptrs
	Node* h = other.m_head;
	other.m_head = m_head;
	m_head = h;

	//swap the tail ptrs
	Node* t = other.m_tail;
	other.m_tail = m_tail;
	m_tail = t;
}

//Public implementations using Map functions

bool combine (const Map& m1, const Map& m2, Map& result)
{
	KeyType key; ValueType value;
	bool noDuplicateError = true; //becomes false if duplicate errors occur

	Map m;
	result = m; //clears result

	for (int i = 0; i < m1.size(); i++) //for each Node in m1
	{
		m1.get(i, key, value);
		result.insert(key,value); //puts every Node into result
	}

	for (int j = 0; j < m2.size(); j++) //each Node in m2
	{
		m2.get(j, key, value);
		ValueType testVal;	
		if (result.get(key, testVal)) //if this key has already been inserted
		{
			if (testVal != value) //if the values are different
			{
				result.erase(key);
				noDuplicateError = false; //found a duplicate error;
				continue; //don't re-add it to the list
			}
			else
				continue; //do nothing instead of trying to add it again
		}
		result.insert(key, value); //if the key is not already in result, add it
	}

	return noDuplicateError; 
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
	KeyType key; ValueType value;

	Map m;
	result = m; //clears result

	for (int i = 0; i < m1.size(); i++) //for each Node in m1
	{
		m1.get(i, key, value);
		result.insert(key,value); //puts every Node into result
	}

	for (int j = 0; j < m2.size(); j++) //each Node in m2
	{
		m2.get(j, key, value);	
		if (result.contains(key)) //if this key has already been inserted
			result.erase(key);
	} 
}


//Test functions

/*#include <cassert>
  #include <iostream>
int main()
{
	Map m; //checks the constructor
	assert(m.empty()); //test empty
	assert(m.insert("Bob", 1)); //insert
	assert(!m.empty()); //test not empty

	assert(!m.insert("Bob", 2)); //insert should fail because Bob already there
	assert(m.update("Bob", 5)); //should update bc bob already exists
	assert(m.insert("Joe", 3)); //insert
	assert(m.insertOrUpdate("Joe", 4)); //should update + return true
	assert(m.insertOrUpdate("Joseph", 10)); //should insert + return true
	assert(!m.update("Aaa", 3)); //should do nothing + return true

	assert(m.size() == 3); //should be 3 items

	Map mcopy(m); //testing the copy constructor
	assert(mcopy.size() == m.size() && mcopy.contains("Bob")
		    && mcopy.contains("Joseph") && mcopy.contains("Joe"));

	
	assert(m.erase("Bob")); //should return true + erase
	assert(!m.erase("Aaa")); //should return false + do nothing

	assert(m.size() == 2); //just erased an item
	assert(m.contains("Joe")); //Joe should still exist
	assert(m.contains("Joseph")); //Joseph should still exist in Map
	assert(!m.contains("Bob")); //Bob should have been erased
	assert(!m.contains("Aaa")); //Aaa should not be in the Map

	KeyType key; ValueType val;

	key = "Aaa";
	assert(!m.get(key, val)); //checking that it correctly returns false

	key = "Joe";
	assert(m.get(key, val));
	assert(val == 4); //get should have found Bob and updated val
	
	int i = 0;
	assert(m.get(i, key, val)); //checking the alternate get
	i = m.size();
	assert(!m.get(i, key, val)); //i is now too big, should fail
	
	Map m2;

	m.swap(m2);
	assert(m.empty() && !m2.empty() && m2.size() == 2); //checking the swap worked
	assert(m2.contains("Joe") && m2.contains("Joseph")); //ditto


	Map m3;
	Map m4;
	Map mresult;

	assert(combine(m3, m4, mresult));
	assert(mresult.empty()); //checking that combine works with empties
	subtract(m3, m4, mresult);
	assert(mresult.empty()); //checking that subtract works with empties

	m3.insert("Fred", 123);
	m3.insert("Ethel", 456);
	m3.insert("Lucy", 789);

	assert(combine(m3, m4, mresult)); //checking combine
	assert(mresult.size() == 3); //checking that combine works with 1 empty
	assert(m4.empty());

	m4.insert("Ricky", 321);
	m4.insert("Ethel", 123);
	m4.insert("Lucy", 789);

	assert(!combine(m3, m4, mresult)); //checking combine returns false for duplicates
	assert(mresult.size() == 3 && !mresult.contains("Ethel") 
			&& mresult.contains("Lucy"));
	//still should modify mresult

	mresult.insert("Aaa", 999);
	assert(!combine(m3, m4, mresult));
	assert(mresult.size() == 3 && !mresult.contains("Ethel") 
			&& mresult.contains("Lucy"));
	//combine should delete extraneous values

	subtract(m3, m4, mresult);
	assert(mresult.size() == 1 && !mresult.contains("Lucy")
		    && !mresult.contains("Ethel"));

	Map empty;
	subtract(m3, empty, mresult);
	assert(mresult.size() == m3.size()); //checks when subtract an empty
	subtract(empty, m3, mresult);
	assert(mresult.empty()); //checks when subtracting from an empty
	subtract(m3, m3, mresult);
	assert(mresult.empty()); //checks aliasing performs correctly
	subtract(empty, empty, mresult);
	assert(mresult.empty()); //checks aliasing performs correctly

	m3 = m4; //tests the =operator
	assert(m3.contains("Ricky") && !m3.contains("Fred"));

	
	m3 = empty; //tests =operator with an empty
	assert(m3.empty());
	empty = m4; //tests the other side
	assert(empty.contains("Lucy") && empty.contains("Ricky") 
			&& empty.contains("Ethel") && empty.size() == 3);
	  
	empty = empty;
	assert(empty.size() == 3); //tests aliasing

	cout << "All tests passed." << endl;
}

*/