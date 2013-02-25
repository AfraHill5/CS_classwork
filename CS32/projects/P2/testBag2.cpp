//test function; will not be turned in

#include "Bag.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
	Bag b;
	assert (b.empty() == 1);         //empty bag
	assert (b.size() == 0);          //no items
	assert (b.uniqueSize() == 0);    //no items

	b.insert(12);                   //testing the insert function
	b.insert(24);
	b.insert(24);                   //duplicates
	b.insert(36);
	b.insert(12);                   //duplicates
	b.insert(12);
	b.insert(24);

	assert (b.size() == 7);           //7 items have been inserted
	assert (b.uniqueSize() == 3);     //3 different items

	b.erase(24);                     //erases one duplicate
	b.eraseAll(12);                  //erases all duplicates

	assert (b.size() == 3);           //4 items have been erased
	assert (b.uniqueSize() == 2);     //2 different items yet
	assert (b.contains(24) == 1);     //it does contain this
	assert (b.contains(25) == 0);     //does not contain this
	assert (b.count(36) == 1);        //1 instance
	assert (b.count(24) == 2);        //2 instances
	assert (b.count(99) == 0);        //0 instances

	Bag c;

	c.insert(12);                    //checking the insert function again
	c.insert(14);
	c.insert(4);
	c.insert(1);
	c.insert(12);
	c.insert(2);
	c.insert(1);

	assert (c.size() == 7);           //7 items
	assert (c.uniqueSize() == 5);
	assert (c.contains(14) == 1);     //contains 14
	assert (c.contains(25) == 0);     //does not contain 25
	assert (c.count(1) == 2);         //2 instances of item 1
	assert (c.count(14) == 1);        //1 instance of item 14
	assert (c.count(999) == 0);       //0 instances of item 999
	



	Bag d, e;

	d.insert(1);
	d.insert(2);
	d.insert(2);
	d.insert(3);
	d.insert(3);
	d.insert(3);

	e.insert(4);
	e.insert(5);
	e.insert(5);
	e.insert(6);
	e.insert(6);
	e.insert(6);

	//d = 1, 2, 2, 3, 3, 3
	//e = 4, 5, 5, 6, 6, 6


	Bag result;
	result.insert(9);             //testing that the combine function correctly deletes other 
	result.insert(99);            //values in the result bag 

	combine(d,e,result);

	assert(result.size() == 12);   //checks that all values have been copied
	assert(result.contains(1) == 1 && result.contains(2) == 1 && result.contains(3) == 1);   //checks that the first bag was copied
	assert(result.contains(4) ==1 && result.contains(5) == 1 && result.contains(6) == 1);    //checks that the second bag was copied
	assert(result.contains(9) == 0 && result.contains(99) == 0);  


	b = c;
	assert(b.contains(14) == 1 && b.contains(12) == 1 && b.contains(2) == 1 && b.contains(24) == 0); //checks that the copy constructor successfully copied the right side to the left
	assert(c.contains(14) == 1 && c.contains(12) == 1 && c.contains(2) == 1 && c.contains(24) == 0);


	d.swap(e);
	assert(d.contains(4) == 1 && d.contains(5) == 1 && d.contains(6) == 1 && d.contains(1) == 0); //checks that the swap function correctly swaps bags
	assert(e.contains(1) == 1 && e.contains(2) == 1 && e.contains(3) == 1 && e.contains(4) == 0);

	Bag f, g;
	f.insert(1);
	f.insert(1);
	f.insert(2);
	f.insert(2);
	f.insert(3);
	//f = 1, 1, 2, 2, 3

	g.insert(1);
	g.insert(2);
	g.insert(3);
	g.insert(4);
	g.insert(5);
	//g = 1, 2, 3, 4, 5

	subtract(f,g,result);

	   //result should be f-g or 1, 2
	assert(result.contains(1) == 1 && result.contains(2) == 1 && 
		result.contains(3) == 0 && result.contains(4) == 0 && result.size() == 2);          //checks that the subtract function works
}