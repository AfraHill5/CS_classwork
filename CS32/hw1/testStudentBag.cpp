#include "Bag.h"
#include "studentBag.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    StudentBag b;
	b.add(42);
	b.add(42);
	b.add(42);
	b.add(472);
	b.add(1);
	cout << "Size ?= 5   " << b.size() << endl;
	cout << "Printing all IDs: " << endl;
	b.print();
}