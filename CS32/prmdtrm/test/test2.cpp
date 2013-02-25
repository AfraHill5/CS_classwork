#include <iostream>
using namespace std;

struct Node
{
	int val;
	Node* next;
};

int oddCount(Node* head)
{
	if (!head)
		return 0;
	if (head->val % 2 == 1)
		return (1 + oddCount(head->next));
	return (oddCount(head->next));
}	

int main()
{
	Node* head = new Node;
	head->val = 11;
	Node* next = new Node;
	head->next = next;
	next->val = 21;
	Node* final = new Node;
	next->next = final;
	next->val = 30;
	int count = oddCount(head);
	cout << count << endl;
}



