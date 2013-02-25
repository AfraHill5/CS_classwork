#ifndef _MAPPER_H_
#define _MAPPER_H_

template<typename T>
class StringMapper
{
public:
    StringMapper();
    ~StringMapper();
    void insert(std::string from, const T& to);
    bool find(std::string from, T& to) const;
    bool getFirstPair(std::string& from, T& to);
    bool getNextPair(std::string& from, T& to);
    int size() const;

private:
	struct SearchNode //used for the binary search tree
	{
		std::string stringValue;
		T TValue; //holds the 2 values being stored
		SearchNode* less;
		SearchNode* greater;
	};

	struct ListNode //used for the linked list keeping track of the searchnodes
	{
		SearchNode* value; //points to a value in the binary search tree
		ListNode* next; //next value in the linked list
	};

	ListNode* m_listHead; //points to the first value in the linked list
	ListNode* m_listCurr; //points to the current iteration in the list
	SearchNode* m_searchHead; //points to the first value in the search tree
};

template<typename T>
StringMapper<typename T>::StringMapper()
{
	m_searchHead = NULL; //currently no values in the binary search tree
	m_listHead = NULL; //no values in the list
}

template<typename T>
StringMapper<typename T>::~StringMapper()
{
	ListNode* temp = m_listHead;
	while (temp) //deletes every value in the binary search tree
	{
		ListNode* nextNode = temp->next;
		delete temp->value;
		delete temp;
		temp = nextNode;
	}
}

template<typename T>
void StringMapper<typename T>::insert(std::string from, const T& to)
{
	if (m_searchHead == NULL) //if there are no values yet
	{
		m_searchHead = new SearchNode;
		m_searchHead->stringValue = from;
		m_searchHead->TValue = to;
		m_searchHead->greater = NULL;
		m_searchHead->less = NULL; //initializes the first value
		m_listHead = new ListNode;
		m_listHead->value = m_searchHead;
		m_listHead->next = NULL;
		return;
	}
	SearchNode* searchIter = m_searchHead;
	SearchNode* a = NULL; //used to keep track of the node so the list can link in.
	while (searchIter->less || searchIter->greater) //while the iteration is not at a leaf
	{
		if (from < searchIter->stringValue) //if there is not a less pointer, and the current string input is less than the node
		{
			if (searchIter->less) //if there is already a less node
				searchIter = searchIter->less; //continues down the tree
			else //found where to insert the item
				break;
		}

		else //from > searchIter->stringValue 
		{
			if (searchIter->greater) //if there is already a greater node
				searchIter = searchIter->greater;
			else //found where to insert the item
				break;
		}
	}
	//the spot to insert the item has now been found
	if (searchIter->TValue == to) //if the URLs are the same, the story shouldn't be added twice
		return;
	if (from < searchIter->stringValue)
	{
		searchIter->less = new SearchNode; 
		searchIter->less->stringValue = from;
		searchIter->less->TValue = to;
		searchIter->less->less = NULL;
		searchIter->less->greater = NULL; //initializes the new search node
		a = searchIter->less; //to be used later to link the linked list in
	}
	else //from is greater than searchIter's stringValue
	{
		searchIter->greater = new SearchNode;
		searchIter->greater->stringValue = from;
		searchIter->greater->TValue = to;
		searchIter->greater->less = NULL;
		searchIter->greater->greater = NULL; //initializes the new search node
		a = searchIter->greater; //to be used later to link in the linked list
	}

	ListNode* listIter = m_listHead;
	while (listIter->next) //gets to the end of the linked list
		listIter = listIter->next;

	listIter->next = new ListNode;
	listIter->next->value = a; //a was the newly inserted search node
	listIter->next->next = NULL; //last item in the list
}

template<typename T>
bool StringMapper<typename T>::find(std::string from, T& to) const
{
	SearchNode* searchIter = m_searchHead;
	while (searchIter)		//runs through the whole tree
	{
		if (from == searchIter->stringValue)
		{
			to = searchIter->TValue; //copies over the T value
			return true;
		}

		else if (from > searchIter->stringValue) //if the searched string is greater than the current
			searchIter = searchIter->greater;
		else
			searchIter = searchIter->less;
	}

	return false; //didn't find it if it gets here
}

template<typename T>
bool StringMapper<typename T>::getFirstPair(std::string& from, T& to)
{
	if (! m_listHead) //returns false if no values
		return false;

	m_listCurr = m_listHead;
	from = m_listCurr->value->stringValue;
	to = m_listCurr->value->TValue;
	return true;
}

template<typename T>
bool StringMapper<typename T>::getNextPair(std::string& from, T& to)
{
	m_listCurr = m_listCurr->next;
	if (! m_listCurr) //returns false if last value
		return false;
	
	from = m_listCurr->value->stringValue;
	to = m_listCurr->value->TValue;
	return true;
}

template<typename T>
int StringMapper<typename T>::size() const
{
	int count = 0; //keeps track of the number of nodes
	for (ListNode* temp = m_listHead; temp != NULL; temp = temp->next) //goes through the list and adds one for each item
		count++;
	return count;
}
#endif // _MAPPER_H_
