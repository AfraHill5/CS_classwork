//Notes 3/2

//AVL tree: a binary tree with at max 1 extra item on the left side than the right or vice versa.

//there are also 2-3 trees and 2-3-4 trees. A 2-3 tree is a tree where every node either has 2 elements and 3 children, or 1 element and 2 children.
//leaves have no no children and 1 or 2 elements.

//2-3-4 trees are called red-black trees. they are essentially a representation of a 2-3-4 tree as a binary tree. It's a "sort of" balanced binary tree, 
//that we are willing to let become unbalanced for some operations.

//we can implementa a simple tree using the c++ lib <set>
#include <set>
using namespace std;

set<int> s;
s.insert(10);
s.insert(30);
s.insert(20);
s.insert(30);
cout << s.size(); //3
set<int>::iterator p = s.find(20);
if (p != s.end())
	cout << *p; //20
	
s.erase(30);
cout << s.size(); //2

for (p = s.begin(); p != s.end(); p++)
		cout << *p << endl;

//most people tend to find the map type more useful than the set. maps utilize key-value pairs -- they link one value with another, ex: a map could be used
//to keep track of debts by linking a name with a dollar amount. (a string and a number)

#include <map>
using namespace std;

map<string, double> ious;
string name;
double amt;

while (cin >> name >> amt)
	ious[name] += amt;

for (map<string, double>::iterator p = ious.begin(); p != ious.end(); p++)
	cout << p->first << "owes me $" << p->second << endl;
	
//for your map parameters, if you want one of them to be another datatype you can do this:
map<string, list<PhoneNumber> >;
//just make sure you put a space between the 2 >>'s.

