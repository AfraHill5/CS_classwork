	// Return true if any of the array elements is negative, false
	// otherwise.
bool anyNegative(const double a[], int n)
{
	if (n <= 0)
		return false; //no values to test
	if (n == 1)
		return (*a < 0); //base case

	return ((*a < 0) || (anyNegative(a+1, n-1)));
}

	// Return the number of negative elements in the array.
int countNegatives(const double a[], int n)
{
	if (n <= 0) //base case
		return 0;
	int thisNeg = 0;
	if (*a < 0) //1 if negative, 0 otherwise
		thisNeg++;
	return (thisNeg + (countNegatives(a+1, n-1)));
}

	// Return the subscript of the first negative element in the array.
	// If no element is negative, return -1.
int firstNegative(const double a[], int n)
{
	int count;
	if (n <= 0)
		return -1;
	if (*a < 0)
		return 0;
	count = (1 + firstNegative(a+1, n-1));

	if (count == 0) //couldnt find a negative
		return -1;
	else
		return count;
}

	// Return the subscript of the smallest element in the array.  If
	// more than one element has the same smallest value, return the
	// smallest index of such an element.  If the array is empty,
	// return -1.
int indexOfMin(const double a[], int n)
{
	if (n <= 0)
		return -1;
	if (n == 1)
		return 0; //only one element so it must be the minimum
	if (n == 2) //compare the 2
	{
		if (a[0] > a[1])
			return 1; //looking for smallest
		else
			return 0;
	};
	int next = 1 + indexOfMin(a+1, n-1); //have to add 1 because a is shifted
	if (a[0] > a[next])
		return next;
	else
		return 0;
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
	if (n2 <= 0)
		return true; //matched the whole string
	if (n1 <= 0) 
		return false; //reached the end, no matches
	
	if (*a1 == *a2) //match of first in string
		return (includes(a1+1, n1-1, a2+1, n2-1));
	else
		return (includes(a1+1, n1-1, a2, n2));
}