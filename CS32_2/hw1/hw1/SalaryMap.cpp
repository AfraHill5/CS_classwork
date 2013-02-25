#include "SalaryMap.h"
#include <iostream>
#include <string>

using namespace std;
SalaryMap::SalaryMap()
{}

bool SalaryMap::add(string name, double salary)
{
	return (m_salaries.insert(name, salary));
}

bool SalaryMap::raise(string name, double pct)
{
	if (pct < -100 || !m_salaries.contains(name))
		return false;

	double oldSal; //holds the old salary of the employee
	m_salaries.get(name, oldSal);
	m_salaries.update(name, oldSal + (pct*oldSal*.01)); //updates the salary + the pct
	return true;
}

double SalaryMap::salary(string name) const
{
	double sal;
	if (m_salaries.get(name, sal))
		return sal;

	return -1; //didn't find the key name in the list
}

int SalaryMap::size() const
{
	return m_salaries.size();
}

void SalaryMap::print() const
{
	string name;
	double salary;
	for (int i = 0; i < size(); i++)
	{
		m_salaries.get(i, name, salary);
		cout << name << " " << salary << endl;
	}
}

