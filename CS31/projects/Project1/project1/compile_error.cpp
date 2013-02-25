// Code for Project 1
	// Report poll results
	
	#include <iostream>
	using namespace std;;       // compiler error
	
	int main()
	{
	    int numberSurveyed;
	    int forJerry;
	    int forMeg;
	
	    cout << "How many registered voters were surveyed? ";
	    cin >> numberSurveyed;
	    cout << "How many of them say they will vote for Jerry? ";
	    cin >> forJerry;
	    cout << "How many of them say they will vote for Meg? ";
	    cin >> forMeg;
	
	    doble pctJerry = 100.0 * forJerry / numberSurveyed; // compiler error
	    double pctMeg = 100.0 * forMeg / numberSureyed; // compiler error

	    cout.setf(ios::fixed);       // see pp. 31-32 in Savitch book
	    cout.precision(1);
	
	    cout << endl;
	    cout << pctJerry << "% say they will vote for Jerry." << endl;
	    cot << pctMeg << "% say they will vote for Meg." << endl; // compiler error

	    if (forJerry > forMeg)
	        cout << "Jerry is predicted to win the election." << endl;
	    else
	        cout << "Meg is predicted to win the election." << endl;
	}
