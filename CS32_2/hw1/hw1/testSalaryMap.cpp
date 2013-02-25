#include "SalaryMap.h"

using namespace std;

int main()
{
	SalaryMap s;
	s.add("Joe", 20000);
	s.add("John", 30000);

	s.raise("Joe", 5.0);
	s.raise("John", -4.5);

	cout << "John's salary is " << s.salary("John") << endl;
	cout << "There are " << s.size() << " employees." << endl;
	cout << "Their names are: \n";
	s.print();
}
