#include <iostream>
using namespace std;

	int main()
	{
	    int side;

	    cout << "Enter a number: ";
	    cin >> side;

	    for (int i = 0; i < side; i++)
	    {
			int j = 0;
			while (j <= i )
			{
				cout << '#';
				j++;
			}

		cout << "\n";
	    }
	}

