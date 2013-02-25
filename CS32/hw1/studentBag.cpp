#include "studentBag.h"
#include <iostream>
using namespace std;

StudentBag::StudentBag()
{
	//works with default compiler-generated constructor
}

bool StudentBag::add(unsigned long id)
{
	return m_studentBag.insert(id); //calls the insert function on studentBag
}

int StudentBag::size() const
{
	return m_studentBag.size(); //calls the size function on studentBag
}

void StudentBag::print()
{
	m_studentBag.start(); //resets the finger to 0
	while (!m_studentBag.ended())
	{
		for (int i = 0; i < m_studentBag.currentCount(); i++) //outputs one line for each count
		{
			cout << m_studentBag.currentValue() << endl;
		}
		m_studentBag.next();
	}
}

//The reason print() cannot be declared constant is because in order to print every element of m_studentBag,
//it has to call the Bag functions start() and next(), which modify the m_finger private element of the Bag
//class. Thus it really isn't a constant function as it modifies the Bag.