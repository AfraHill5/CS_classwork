	// Return the number of ways that all n2 elements of a2 appear
	// in the n1 element array a1 in the same order (though not
	// necessarily consecutively).  The empty sequence appears in a
	// sequence of length n1 in 1 way, even if n1 is 0.
	// For example, if a1 is the 7 element array
	//	10 50 40 20 50 40 30
	// then for this value of a2     the function must return
	//	10 20 40			1
	//	10 40 30			2
	//	20 10 40			0
	//	50 40 30			3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0)
		return 1; //matched the whole string
	if (n1 <= 0 || n2 > n1) 
		return 0; //reached the end
	
	if (*a1 == *a2) //match of first in string
		return (countIncludes(a1+1, n1-1, a2, n2) + countIncludes(a1+1, n1-1, a2+1, n2-1));
		//need to check both different possibilities of combinations
	else
		return (countIncludes(a1+1, n1-1, a2, n2));
}

	// Exchange two doubles
void exchange(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

	// Rearrange the elements of the array so that all the elements
	// whose value is < splitter come before all the other elements,
	// and all the elements whose value is > splitter come after all
        // the other elements.  Upon return, firstNotLess is set to the index
        // of the first element in the rearranged array that is >= splitter,
	// or n if there is no such element, and firstGreater is set to
	// the index of the first element that is > splitter, or n if
	// there is no such element.
	// In other words, upon return from the function, the array is a
	// permutation of its original value such that
	//   * for 0 <= i < firstNotLess, a[i] < splitter
	//   * for firstNotLess <= i < firstGreater, a[i] == splitter
	//   * for firstGreater <= i < n, a[i] > splitter
	// All the elements < splitter end up in no particular order.
	// All the elements > splitter end up in no particular order.
void split(double a[], int n, double splitter, int& firstNotLess, int& firstGreater)
{
	if (n < 0)
	    n = 0;
	
	    // It will always be the case that just before evaluating the loop
	    // condition:
	    //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
	    //  Every element earlier than position firstNotLess is < splitter
	    //  Every element from position firstNotLess to firstUnknown-1 is
	    //    == splitter
	    //  Every element from firstUnknown to firstGreater-1 is not
	    //     known yet
	    //  Every element at position firstGreater or later is > splitter
	
	firstNotLess = 0;
	firstGreater = n;
	int firstUnknown = 0;
	while (firstUnknown < firstGreater)
	{
            if (a[firstUnknown] > splitter)
            {
                firstGreater--;
                exchange(a[firstUnknown], a[firstGreater]);
            }
            else
            {
                if (a[firstUnknown] < splitter)
                {
                    exchange(a[firstNotLess], a[firstUnknown]);
                    firstNotLess++;
                }
                firstUnknown++;
            }
	}
}

	// Rearrange the elements of the array so that
	// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
	// If n <= 1, do nothing.
void order(double a[], int n)
{
	if (n <= 1)
		return;
	int firstNotLess = 0;
	int firstNotGreater = 0;
	split(a, n, a[0], firstNotLess, firstNotGreater);
	//order first half
	order(a, firstNotLess);
	//second half
	order(a + firstNotGreater, n-firstNotGreater);
}

#include <cassert>
#include <iostream>
using namespace std;

int main () 
{
	double a1Test[7] =  {10, 50, 40, 20, 50, 40, 30};
	double a2Test1[3] = {10, 20, 40};
	double a2Test2[3] = {10, 40, 30};
	double a2Test3[3] = {20, 10, 40};
	double a2Test4[3] = {50, 40, 30};

	assert(countIncludes(a1Test, 7, a2Test1, 3) == 1);
	assert(countIncludes(a1Test, 7, a2Test2, 3) == 2);
	assert(countIncludes(a1Test, 7, a2Test3, 3) == 0);
	assert(countIncludes(a1Test, 7, a2Test4, 3) == 3);
	assert(countIncludes(a1Test, 7, a2Test4, -1) == 1);

	double orderThis[10] = {3, 7, 23, 7, 2, 54, 87, 3, 4, 8};
	double orderThis2[10] = {-4, 2, 7, 3, 9, 4, -1, 65, -98, 6};
	double zeroOrder[10] = {0, 6, 3, -2, 0, 5, 0, 8, 23, -2};

	order(orderThis, 10);
	order(orderThis2, 10);
	order(zeroOrder, 10);

	for (int i = 0; i < 10; i++)
		cout << orderThis[i] << endl;
	cout << "\n\n";

	for (int j = 0; j < 10; j++)
		cout << orderThis2[j] << endl;
	cout << "\n\n";

	for (int k = 0; k < 10; k++)
		cout << zeroOrder[k] << endl;
	cout << "\n\n";

	cout << "All tests passed." << endl;
}