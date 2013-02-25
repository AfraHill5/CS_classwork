//Notes 2/7/11

//Constructor guidelines:
//1.Construct the base part
//2.Construct the data members
//3.Execute the body of the constructor

//Destructors are the same except backwards (3->1)

//Base classes cannot have a pure destructor function because it will always be called whenever the base class goes away.
//Whenever you delete a derived class, the base class destructor will be called.

//The trick with recursive functions is to make sure that each instance that the function is called deals with a smaller and smaller problem.

//optimized code for countNegatives function:
int countNegatives (const double a[], int n)
{
	if (n < 0)
		return 0;
	int t = (a[0] < 0) //1 if true, 0 if false
	return t + countNegatives(a+1, n-1);
}

//You use recursion when a recursive path through a function might make more than one recursive call in a given execution. In this case it is much
//easier to use recursion than a stack, and easier to follow.

//Midterm problems: some ask for output from a piece of code (what does this do?), some ask for debugging a piece of code, some ask for simply writing functions.

int minimum(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

double minimum(double a, double b)
{
	if (a < b)
		return a;
	else
		return b;
}

int main()
{
	int k;
	cin >> k;
	cout << minimum(k,10) / 2;
	double x;
	...
	double y = 3 * minimum(x*x, x+10);
	...
	int z = minimum(0,3*k - k + 4);
	...
}

//This works but the double and integer version of minimum are exactly the same code. We would like to be able to automate how to do the minimum of two things
//of the same type rather than writing code for every single type. This is called a TEMPLATE.

//In C++ you can do the following to create a template:

T minimum(T a, T b)
{
	if (a < b)
		return a;
	else
		return b;
}

//This doesn't actually work right out of the box, though. You need to tell the compiler that this function is a template using this syntax:

template<typename T> //this tells the compiler that T is a template.
T minimum(T a, T b)
{
	if (a < b)
		return a;
	else
		return b;
}

int main()
{
	int k;
	cin >> k;
	cout << minimum(k, 10) / 2; //At this point the compiler sees the minimum call, realizes you did not declare a function called minimum, and goes through
								//what is called "template argument deduction." It tries to deduce what T should be replaced by in order to do the right thing.
								//Since the second element of the call is an int, it decided to replace T with an int and call the function. If instead you
								//declared k a double, the compiler would automatically decide to replace T with double.
	double x;
	...
	double z = 3 * minimum(x*x, x+10); //in this case the compiler automatically assigns T to be a double.
	...
	int z = minimum(0, 3*k - k + 4);
}

//What if I call this function in main:
int k;
minimum(k, 3.5); //Error! If you confuse the compiler by passing it an int and a double, it won't compile this. It cannot do automatic conversions.

//What about
string a,b;
minimum(a, b); //This compiles. They are both strings, so T is set to string, and the < operator has been overloaded for the string class, so it works.

//What about
char ca1[100];
char ca2[100]; //2 Cstrings.
char* ca3 = minimum(ca1, ca2); //This compiles, but keep in mind what this does: it is comparing ca1 and ca2, 2 pointers to arrays, so it is only looking 
								//at the first character in the cstring! This will compile but will not give you the correct answer.

//But if you want this to work, you can write out an overloaded version of the function for cstrings, using strcmp, and it will work.

