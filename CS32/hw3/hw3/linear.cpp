//Zach North
//603 885 768
//Homework 3, Problem 2

#include <iostream>
#include <cassert>
using namespace std;


// Return true if any of the array elements is negative, false
// otherwise.
bool anyNegative(const double a[], int n)
{
	if (n == 0) //reached the end of the array
		return false;
	if (*a < 0) //if the currently pointed value is negative, returns true
		return true;
	//recursive case
	return (anyNegative(a+1, n-1));
}

	  // Return the number of negative elements in the array.
int countNegatives(const double a[], int n)
{
	int count = 0; //counts the negatives
	if (n == 0)
		return 0;
	if (*a < 0) //if the currently pointed value is negative
		count++;
	return (count + countNegatives(a+1, n-1)); //recursive case
}

	  // Return the subscript of the first negative element in the array.
	  // If no element is negative, return -1.
int firstNegative(const double a[], int n)
{
	if (!anyNegative(a,n)) //if there are no negative values in the array, stop and return -1
		return -1;
	if (*a < 0) //if it found the negative value
		return 0;
	else //recursive function; continue on to the next element of the array
		return (1 + firstNegative(a+1, n-1));
}

	  // Return the subscript of the largest element in the array.  If
	  // more than one element has the same largest value, return the
	  // smallest index of such an element.  If the array is empty,
	  // return -1.
int indexOfMax(const double a[], int n)
{
	if (n < 2) //if there is only one element left, it is the biggest.
		return 0;
	if (a[0] > a[1 + indexOfMax(a+1, n-1)]) //if the current value is the biggest left in the array, stop searching
		return 0;
	else //continue searching
		return 1 + indexOfMax(a+1, n-1);
}

	  // If all n2 elements of a2 appear in the n1 element array a1, in
	  // the same order (though not necessarily consecutively), then
	  // return true; otherwise (i.e., if the array a1 does not include
	  // a2 as a not-necessarily-contiguous subsequence), return false.
	  // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
	  // For example, if a1 is the 7 element array
	  //    10 50 40 20 50 40 30
	  // then the function should return true if a2 is
	  //    50 20 30
	  // or
	  //    50 40 40
	  // and it should return false if a2 is
	  //    50 30 20
	  // or
	  //    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0) //if the function reached the end of the searching array
		return true;
	if (n1 <= 0) //if the function reached the end of the array to be searched
		return false;
	
	if (*a1 == *a2)
		return (includes(a1+1, n1-1, a2+1, n2-1)); //continue searching, using the next term
	else
		return (includes(a1+1, n1-1, a2, n2)); //the current term did not match, so go on to the next term in the array to be searched
}


