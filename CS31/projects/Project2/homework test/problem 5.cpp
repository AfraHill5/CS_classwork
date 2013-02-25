#include <iostream>
using namespace std;

int main()
{
	int year;
	cout << "This program will tell you the governor elect California in the year you input.\n";
	cout << "What year will you choose? ";
	cin >> year;

	switch (year)
	{
	case 2003:
		cout << "Schwarzenegger\n";
		break;
	case 1998:
		cout << "Davis\n";
		break;
	case 2010:
		cout << "Who knows?\n";
		break;
	case 1990:
		cout << "Wilson\n";
		break;
	case 1994:
		cout << "Wilson\n";
		break;
	default:
		cout << "Someone\n";
	}
}
