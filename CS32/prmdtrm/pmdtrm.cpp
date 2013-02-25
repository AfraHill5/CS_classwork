//Practice Midterm 


//GIVEN:

struct Node
{
	Itemtype m_value;
	Node* m_prev;
	Node* m_next;
}

class SortedLinkedList
{
	public:
		SortedLinkedList();
		bool insert(const ItemType &value);
		Node* search(const ItemType &value) const;
		void remove(Node *node);
		int size() const {return m_size;}
		void printIncreasingOrder() const;
	private:
		Node* m_head;
		Node* m_tail;
		int m_size;
};

//IMPLEMENT:

//a: the constructor SortedLinkedList().
SortedLinkedList::SortedLinkedList()
{
	m_head = NULL;
	m_tail = NULL;
	m_size = 0;
}

//b: the function insert(). If a node with the same value is already in  the list,
//	 do not insert a new node. Return true if a new node is successfully inserted, 
//   and return false otherwise. You may assume that ItemType has <, >, and == 
//   operators properly implemented.

bool SortedLinkedList::insert(cont ItemType &value)
{
	Node* current = m_head;
	Node* prev = current;
	while (current)
	{
		if (current ->m_value == value)
			return false;
		if (current->m_value > value)
		{
			prev = current;
			current = current->m_next;
		}
		else //found where to insert the node
		{
			if (prev)
				prev->m_next = current;
			if (current->m_next)
				current->m_next->m_prev = prev;
			Node* n = new Node;
			n->m_next = current->m_next;
			n->m_prev = prev;
			n->m_value = value;
			m_size++;
			return true;
		}
	}
	Node* n = new Node;
	n->m_prev = m_tail;
	m->m_value = value;
	m_size++;
	return true;
}

//c: the function search(), which returns the pointer to the node with the specified value.

Node* SortedLinkedList::search(const Itemtype &value) const
{
	Node* temp = m_head;
	while (temp && temp->m_value != value)
		temp = temp->m_next;
	if (temp)
		return temp;
	else
		return NULL;
}

//d: remove(). Assume node is either NULL (in which case you would simply return) or a valid
//	 pointer to a Node in the list, as found in search().

void SortedLinkedList::remove(Node* node)
{
	if (node == NULL)
		return;
	Node* temp = m_head;
	while (temp != node)
		temp = temp->m_next;
	//at this point we have reached the correct node to delete; now must link the pointers
	if (temp->m_prev)
		temp->m_prev.m_next = temp->m_next;
	else
		m_head = temp->m_next;

	if (temp->m_next)
		temp->m_next.m_prev = temp->m_prev;
	else
		m_tail = temp->m_prev; 
	delete temp;
	m_size--;
}

//e. printIncreasingOrder(), which prints the values stored in the list in increasing order, one 
//	 value in each line.

void SortedLinkedList::printIncreasingOrder() const
{
	Node* temp;
	while (temp)
	{
		cout << temp->m_value << endl;
		temp = temp->m_next;
	}	
}

//f. The public interface of SortedLinkedList has a problem. More precisely, the user of this class
//   can possibly break the integrity of the sorted linked list, only using the public interface of
//   SortedLinkedList. Demonstrate this problem with an example. Also, suggest a fix, if you have an
//	 idea.

if you search for a node, and then change the value of its m_value, the list may no longer be sorted.



//2
//Make the following code print the elements in a[] in reverse order.
void printArrayInOrder(const double a[], int n)
{
	if (n == 0)
		return;
	
	cout << a[0] << endl;
	printArrayInOrder(a + 1, n - 1)
}

//REVERSED:
void printArrayInReverseOrder(const double a[], int n)
{
	if (n == 0)
		return;
		
	cout << a[n-1] << endl;
	printArrayInOrder(a, n-1);
}

//3
//Given 2 positive ints m & n such that m < n, the greatest common divisor of m and n is the 
//same as the greatest common divisor of m and n-m. Use this fact to write a recursive function
//gcd(). (Suggestion: try a few examples on paper prior to writing code.)

int gcd(int m, int n)
{
	if (n == m)
		return m;
	
	m = n-m;
	if (m < n)
		return gcd(m, n);
	return gcd(n,m);
}
	
//4
//Write a function powerOfTwo that, given a non-negative number x, returns 2^x recursively,
//assuming 2_x is something that can be represented as an integer. Do not use a loop, and do 
//not use the char '*' anywhere in your code.

int powerOfTwo(int x)
{
	if (int x == 0)
		return 1;
	return (powerOfTwo(x-1) + powerOfTwo(x-1));
}

//5
//Consider the following program:

class A
{
	public:
		A(): m_msg("Apple") {}
		A(string msg) : m_msg(msg) {}
		virtual ~A() { message(); }
		void message() const
		{
			cout << m_msg << endl;
		}
	private:
		string m_msg;
};

class B
{
	public:
		B() : A("Orange") {}
		B(string msg) : A(msg), m_a(msg) {}
		void message() const
		{
			m_a.message();
		}
	private:
		A m_a;
};

int main()
{
	A *b1 = new B;
	B *b2 = new B;
	A *b3 = new B("Apple");
	b1->message();
	b2->message();
	b3->message();
	delete b1;
	delete b2;
	delete b3;
}

//OUTPUT:
Orange
Orange
Apple

//if A.message() is virtual:
Orange
Orange
Apple


//6
//Using a stack, write a function that takes in an infix arithmatic expression exp, which
//may involve ()s, {}s, and []s, and returns true if they are balanced, false otherwise.
//If the expression does not include any of the above, return true.

#include <stack>
using namespace std;

bool balanced(const string &exp)
{
	stack<char> charStack;
	for (int i = 0; i < exp.length(); i++)
	{
		if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
			charStack.push(exp[i]);
		if (exp[i] == ')')
		{
			if (charStack.top() != '(')
				return false;
			charStack.pop();
		}
		if (exp[i] == '}')
		{
			if (charStack.top() != '{')
				return false;
			charStack.pop();
		}
		if (exp[i] == ']')
		{
			if (charStack.top() != '[')
				return false;
			charStack.pop();
		}
	}
	if (charStack.size() != 0)
		return false;
	else
		return true;
}


//NACHENBERG REVIEW

//#1
struct Node
{
	int val;
	Node* next;
}

int oddCount(Node* head)
{
	if (!head)
		return 0;
	if (head->val % 2 == 1)
		return (1 + oddCount(head->next));
	return (oddCount(head->next));
}	

//#2
class SeaAnimal
{
	public:
		SeaAnimal(int weight) : m_weight(weight) {};
		virtual void makeNoise() = 0;
		int weight() {return m_weight;}
		virtual void eat(&SeaAnimal victim);
	private:
		m_weight;
}

class Otter : public SeaAnimal
{
	public:
		virtual void makeNoise();
}

class Squid : public SeaAnimal
{
	public:
		virtual void makeNoise();
}

class GiantSquid : public Squid
{
	public:
		GiantSquid() {m_weight = 1000;}
		void eat(&SeaAnimal victim);
}

SeaAnimal :: eat(&SeaAnimal victim)
{
	m_weight += victim.weight();
}

Otter::makeNoise()
{
	cout << "Bark";
}

Squid::makeNoise()
{
	cout << "Squeak";
}
	
GiantSquid::eat(&SeaAnimal victim)
{
	m_weight += victim.weight();
	cout << "Burp";
}

//#3
void addOnes(Node* head)
{
	for (head; head != NULL; head = head->next)
	{
		if (head->val == 0)
		{
			Node* n = new Node;
			n->next = head->next;
			head->next = n;
			n->val = 1;
		}
	}
}	


//write a function to compute x^n using recursion.

int exponentiate(int x, int n)
{
	if (x <= 1)
		return x;
	if (n == 0)
		return 1;
	return (x * exponentiate(x, n-1));
}

