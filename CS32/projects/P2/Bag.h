//Zach North
//P2
//1/24/2011
//Implementation of the Bag function with double linked list

#ifndef BAG_H_DEFINED
#define BAG_H_DEFINED

typedef unsigned long ItemType;

struct Node
{
	ItemType m_item; //item name
	int m_count; //item count
	Node* m_prev; //points to prev node
	Node* m_next; //points to next node
};

class Bag
{
public:
	//housekeeping
	Bag();
	Bag(const Bag& a);
	~Bag();
	Bag& operator=(const Bag& a);

	//functions
	bool empty() const;
	int size() const;
	int uniqueSize() const;
	bool insert(const ItemType& value);
	int erase(const ItemType& value);
	int eraseAll(const ItemType& value);
	bool contains(const ItemType& value) const;
	int count(const ItemType& value) const;
	void swap(Bag& other);

	//iteration functions
	void start();
	void next();
	bool ended() const;
	const ItemType& currentValue() const;
	int currentCount() const;

private:
	Node* m_head; //points at first element
	Node* m_tail; //points at last element
};

//public functions
void combine (Bag& b1, Bag& b2, Bag& result);
void subtract(Bag& b1, Bag& b2, Bag& result);




#endif