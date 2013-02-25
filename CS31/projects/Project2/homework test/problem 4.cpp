#include <iostream>
using namespace std;

int main()
{
	int side;

	cout << "Enter a number: ";
	cin >> side;

	if (side <= 0)
	{
		cout << "Please enter a positive number.\n";
	}
	else
	{
		int i = 0;
	
		while (i < side)
		{
		int j = 0;

			while (j <= i)
			{
				cout << '#';
				j++;
			 }
		
		cout << '\n';
		i++;
		}
	}
}