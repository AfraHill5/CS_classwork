#ifndef MYHASHMAP_INCLUDED
#define MYHASHMAP_INCLUDED

const int DEFAULT_NUM_BUCKETS = 1000000;

#include <string>
#include <algorithm>

template <typename ValueType>
class MyHashMap
{
public:

    MyHashMap(int numBuckets = DEFAULT_NUM_BUCKETS)
    {
		m_table = new Record* [numBuckets];
		for (int i = 0; i < numBuckets; i++)
			m_table[i] = NULL;

		m_linkedListHead = NULL; //no items yet
		m_linkedListIter = NULL;

		m_tableSizeUsed = 0;
		m_numBuckets = numBuckets;
	}

    ~MyHashMap()
    {
		while (m_linkedListHead != NULL)
		{
			Record* curr = m_linkedListHead->item;
			RecordListItem* currListItem = m_linkedListHead;
			m_linkedListHead = m_linkedListHead->next;
			delete curr;
			delete currListItem;
		}
		delete m_table;
    }

    void associate(std::string key, const ValueType& value)
    {
		unsigned keyValue = 0;
		std::string lowKey = key;
		transform(lowKey.begin(), lowKey.end(), lowKey.begin(), tolower);

		for (unsigned i = 0; i < lowKey.size(); i++)
		{
			keyValue += (i+3) * lowKey[i]; //use the ASCII value to gen key
		}

		keyValue %= m_numBuckets; //generate the key to place the record
		
		Record* curr = m_table[keyValue];
		Record* prev = NULL;
		
		while (curr != NULL) //checking for collisions
		{
			if (curr->key == lowKey) //key already exists and just needs update
			{
				curr->val = value;
				return;
			}
			prev = curr;
			curr = curr->next;
		}

		//if it doesn't return in the while loop, new key in the hash
		m_tableSizeUsed++;

		curr = new Record;
		curr->key = lowKey;
		curr->val = value; //package the information into a record object
		curr->next = prev;
		m_table[keyValue] = curr;
		//if this is the first item with the keyvalue, places it in the hash
		//if this is the 2nd+, moves it to the "first" and slides the others back


		//have to also insert into the linked list to keep track
		RecordListItem* currListItem = new RecordListItem;
		currListItem->item = m_table[keyValue];
		currListItem->next = NULL;
		if (m_linkedListHead == NULL) //if it is the first item in the map
			m_linkedListHead = currListItem;
		else //put it at the end of the linked list
		{
			RecordListItem* prevListItem = m_linkedListHead;
			while (prevListItem->next != NULL)
				prevListItem = prevListItem->next;
			prevListItem->next = currListItem;
		}
	}


    const ValueType* find(std::string key) const
    {
		unsigned keyValue = 0;
		std::string lowKey = key;
		transform(lowKey.begin(), lowKey.end(), lowKey.begin(), tolower);
		
		for (unsigned i = 0; i < lowKey.size(); i++)
		{
			keyValue += (i+3) * lowKey[i]; //use the ASCII value to gen key
		}

		keyValue %= m_numBuckets; //generate the key to find the record

		Record* checkThis = m_table[keyValue];
		while (checkThis != NULL)
		{
			if (checkThis->key == lowKey) //found the key
				return &(checkThis->val); //return ptr to the value
			else
				checkThis = checkThis->next;
		}
		return NULL; 
    }

    ValueType* find(std::string key)
    {
		// Do not change the implementation of this overload of find
        const MyHashMap<ValueType>* constThis = this;
        return const_cast<ValueType*>(constThis->find(key));
    }

    ValueType* getFirst(std::string& key)
    {
		if (numItems() == 0)
			return NULL; //no items in the hash to search
		//this initializes the iterator for later getNext calls
		m_linkedListIter = m_linkedListHead;
		key =  m_linkedListHead->item->key;
		return (&(m_linkedListHead->item->val));
	}
    ValueType* getNext(std::string& key)
    {
		if (m_linkedListIter == NULL)
			return NULL; //trying to call when already at end of map

		m_linkedListIter = m_linkedListIter->next;
		if (m_linkedListIter == NULL)
			return NULL; //end of the hash table

		key = m_linkedListIter->item->key;
		return (&(m_linkedListIter->item->val));
    }

    int numItems() const
    {
        return m_tableSizeUsed;
    }

private:
	struct Record //holds the actual records
	{
		std::string key;
		ValueType val;
		Record* next;
	};

	struct RecordListItem //used for the linked list
	{
		Record* item;
		RecordListItem* next;
	};

	int m_tableSizeUsed;
	int m_numBuckets;
	Record** m_table; //the start of the table
	RecordListItem* m_linkedListHead; //the head of the parallel linked list	
	RecordListItem* m_linkedListIter; //used for getFirst, getNext
};

#endif // MYHASHMAP_INCLUDED
