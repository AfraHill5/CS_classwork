#include "temp.h"
#include <iostream>
using namespace std;

int main()
{
	MyHashMap<int> m;
	m.associate("Joe", 3);
	m.associate("John", 4);
	m.associate("Joe", 5);
	m.associate("George", 6);
	m.associate("Andrew", 7);
	m.associate("Bob", 12);
	m.associate("Andrew", 15);
	m.associate("Joe", 3);

	string key;
	int* val;
	for (val = m.getFirst(key);;)
	{
		cout << "Key: " << key << endl;
		cout << "Val: " << *val << endl << endl;

		val = m.getNext(key);
		if (!val)
			break;
	}
}