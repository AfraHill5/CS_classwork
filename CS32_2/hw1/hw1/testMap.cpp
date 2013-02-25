#include <iostream>
#include <cassert>
#include <string>
#include "Map.h"

using namespace std;


int main()
{
    Map m1;
    m1.insert("Fred", 2.956);
	m1.insert("Joe", 2.984);
	m1.insert("Joseph", 1.352);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  &&
           m2.size() == 3  &&  m2.contains("Joseph") && m2.contains("Joe"));
}