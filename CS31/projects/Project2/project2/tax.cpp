//Project 2
//Zach North 603-885-768

#include <string>
#include <iostream>
using namespace std;

int main()
{
	//declaring tax rate constants for use later

	const double topTaxRate = .09;
	const double midTaxRate = .06;
	const double midTaxRateEngSci = .05;
	const double bottomTaxRate = .04;

	//collects the user's name
	string userName;
	cout << "Name: ";
	getline(cin, userName);

	//collects the user's taxable income
	double taxableIncome = 0;
	cout << "Taxable income: ";	
	cin >> taxableIncome;
	cin.ignore (100000, '\n'); // ignores the newline so the next collection will work


	//collects the user's occupation
	string occupation;
	cout << "Occupation: ";
	getline(cin, occupation);

	//collects the user's number of children
	int numberChildren = 0;
	cout << "Number of children: ";
	cin >> numberChildren;

	double taxesPaid = 0;
	int maxTaxBracket; //used to determine top tier tax bracket

	if (taxableIncome > 120000)
		maxTaxBracket = 2; //top bracket
	else if (taxableIncome > 50000 && taxableIncome <= 120000)
		maxTaxBracket = 1; //mid bracket
	else
		maxTaxBracket = 0; // bottom bracket



	//Reduces taxes paid by $200 for every child if taxable income is <120000
	if (maxTaxBracket != 2)
		taxesPaid -= (numberChildren) * 200;

	if ((maxTaxBracket == 2) && occupation != "scientist" && occupation != "engineer") // taxes the decimal at the top rate
	{
		taxesPaid += (((taxableIncome) - 120000) * topTaxRate);
		taxesPaid += (70000 * midTaxRate); // the middle rate
		taxesPaid += (50000 * bottomTaxRate); // the low rate
	}
	else if ((maxTaxBracket == 2) && (occupation == "scientist" || occupation == "engineer")) //taxes the decimal at the top eng/sci rate
	{
		taxesPaid += (((taxableIncome) - 120000) * topTaxRate);
		taxesPaid += (70000 * midTaxRateEngSci); // the middle eng/sci rate
		taxesPaid += (50000 * bottomTaxRate); // the low rate
	}
	else if (maxTaxBracket == 1 && occupation != "scientist" && occupation != "engineer") //taxes the decimal at the medium non-eng/sci rate
	{
		taxesPaid += (((taxableIncome) - 50000) * midTaxRate);
		taxesPaid += (50000 * bottomTaxRate); // the low rate
	}
	else if ((maxTaxBracket == 1) && (occupation == "scientist" || occupation == "engineer")) //taxes the decimal at the medium eng/sci rate
	{
		taxesPaid += (((taxableIncome) - 50000) * midTaxRateEngSci);
		taxesPaid += (50000 * bottomTaxRate); // the low rate
	}
	else
	{
		taxesPaid += (taxableIncome * bottomTaxRate);
	}
	
	//sets the output to be $ format
	cout.setf(ios::fixed);
	cout.precision(2);

	//makes sure that taxes paid are not negative
	if (taxesPaid < 0)
		taxesPaid = 0;

	cout << "---\n";
	
	if (userName == "") //checks to see if username was blank
		cout << "You must enter a name" << endl;
	else if (taxableIncome < 0)//checks to see if taxable income is negative
		cout << "The taxable income must be nonnegative" << endl;
	else if (occupation == "")//checks to see that an occupation was entered
		cout << "You must enter an occupation" << endl;
	else if (numberChildren < 0)//checks to see that the number of children entered is positive
		cout << "The number of children must be nonnegative" << endl;
	else //if all checks pass, displays the user's tax obligation
		cout << userName << " would pay $" << taxesPaid << endl;
}
