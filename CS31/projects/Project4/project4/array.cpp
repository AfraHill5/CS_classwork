//Zach North
//603-885-768
//Project 4

#include <iostream>
#include <string>
using namespace std;

int setAll(string a[], int n, string value) //Assigns value to each of the n elements in the array and return n
{
	if (n < 0)
		return -1;

	for (int k = 0; k < n; k++)
	{
		a[k] = value; //sets value to each element
	}
	return n;
}

int lookup(const string a[], int n, string target) //Returns the position of the first string in the array that is equal to target. 
													//Returns -1 if string does not exist.
{
	if (n < 0) //check that n is positive
		return -1;
	for (int k = 0; k < n; k++)
	{
		if (a[k] == target)
			return k;
	}
	return -1; //returns -1 if search failed
}

int positionOfMax(const string a[], int n) //Returns the position of the string in latest alphabetic order, or -1 if there is no such string
{
	if (n <= 0) //check that n is positive
		return -1;
	string highestString = a[0];
	int highestStringInt = 0;

	for (int k = 0; k < n; k++)
	{
		if (a[k] > highestString)
		{
			highestString = a[k]; //if the current string is the highest, sets it to the value and sets the int to its position
			highestStringInt = k;
		}
	}
	return highestStringInt; //returns the position of the latest alphabetic string
}

int rotateLeft(string a[], int n, int pos) //Eliminates the value at position pos by moving all elements after it one place to the left,
										   //then puts it at the end
{
	string movingString = a[pos]; //stores the element to be moved

	int k = pos;
	while (k < n-1) 
	{
		a[k] = a[k+1]; // moves every array value after pos over 1 to the left
		k++;
	}
	a[n-1] = movingString; //puts the moving string in the final position
	return pos;
}

int rotateRight(string a[], int n, int pos) //same as above except moves value at pos to front
{
	string movingString = a[pos]; //stores the element to be moved

	int k = pos;
	while (k > 0)
	{
		a[k] = a[k-1]; //moves every array value before pos over 1 to the right
		k--;
	}
	a[0] = movingString; // puts the moving string in the first position
	return pos;
}

int flip(string a[], int n) //reverses the order of the elements and returns n
{
	int initialPos = 0, finalPos = n-1;

	for (initialPos; initialPos < (n/2); initialPos++)
	{
		string movingString = a[initialPos]; 
		a[initialPos] = a[finalPos]; 
		a[finalPos] = movingString; //these 3 lines swap the 2 array elements
		finalPos--; //steps through the function
	}
	return n;
}

int isSmaller(int n1, int n2) //simple function to determine which of 2 integers is smaller
{
	if (n1 < n2)
		return n1;
	else
		return n2;
}

int differ(const string a1[], int n1, const string a2[], int n2) //Return the position of the first corresponding elements of a1 and a2 that are not equal
{
	int counter = 0;

	for (int k = 0; k < (isSmaller(n1, n2)); k++) //k < the smaller of the 2 array sizes
	{
		if (a1[k] != a2[k])
			return counter;
		counter++;
	}
}

int subsequence(const string a1[], int n1, const string a2[], int n2) //if all n2 elements of a2 appear in a1, consecutively and in the same order, 
																	  //return the position in a1 where the subsequence begins; more than once, return
																	  //the smallest value when it starts; never appears, return -1
{
	for (int k = 0; k < n1; k++)
	{
		int j = 0; 
		int startValue = k; //marks the start of the subsequence so k can be modified
		int tempK = k; //used to make sure the while loop can step through the k values without skipping any

		while (a1[tempK] == a2[j])
		{
			j++;
			tempK++;
			if (j == n2) //triggers if all elements in n2 match
				return startValue;
		}
	}
	return -1; //no matches
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) //Return the smallest position in a1 of an element that is equal to any
																	//element of a2; return -1 if no elements are equal
{
	for (int k = 0; k < n1; k++) //this steps through a1
	{
		for (int j = 0; j < n2; j++) //steps through a2
		{
			if (a1[k] == a2[j])
				return k;
		}
	}
	return -1; //-1 if the string isnt found
}

int split(string a[], int n, string splitter) //Rearranges the elements of the array so that all the elements whose values are < than
											  //splitter come before all the other elements, and all the elements with values > than
											  //splitter come after all the other elements. Returns the value of the first element that,
											  //after the rearrangement, is >= splitter.
{
	int counter = 0;
	for (int k = 0; k < n; k++)//this moves all values less than splitter to the front
	{
		if (a[k] < splitter)
		{
			rotateRight(a, n, k); //moves this value to the front
			counter++; //adds one to position to indicate split location
		}
	}
	for (int k = n-1; k >= 0; k--) //this moves all values greater than splitter to the back
	{
		if (a[k] > splitter)
			rotateLeft(a, n, k); //moves this value to the front
	}
	
	if (counter != 0)
		return counter; //returns the position of the first value less than splitter
	return n; //returns n if there were none
}

int main() //debug
{
	//SETALL TEST
	string test[19];
	int setAllTest = setAll(test, 19, "this test worked"); // change this to test
	cout << "setAll returns for a = " << setAllTest << endl; // give value returned by setAll
	for (int k = 0; k < setAllTest; k++) // gives each value in the array
		cout << "The " << (k + 1) << "th term in the array is: " << test[k] << endl;

	//LOOKUP TEST
	string test2[10] = {"Joe", "Bob", "Frank", "John", "Mary", "Elizabeth", "Amanda", "Elizabeth", "Bill", "Malisa"}; // change this to test
	int lookupTest = lookup(test2, 10, "Elizabeth"); //change the n values to test
	cout << "lookup returns for b = " << lookupTest << endl; //should give the value in the array position specified

	//POSITIONOFMAX TEST
	int positionOfMaxTest = positionOfMax(test2, 10); //should return the value of the latest alphabetic element; change n values to test
	cout << "positionOfMax returns for b = " << positionOfMaxTest << endl; 

	//ROTATELEFT TEST
	int rotateLeftTest = rotateLeft(test2, 7, 1);
	cout << "The array has been rotated left. The test returns: " << rotateLeftTest << endl;
	for (int k = 0; k < 10; k++) // gives each value in the array
		cout << "The " << (k + 1) << "th term in the array is now: " << test2[k] << endl;

	//ROTATERIGHT TEST
	string test3[10] = {"Joe", "Bob", "Frank", "John", "Mary", "Elizabeth", "Amanda", "Zach", "Bill", "Malisa"}; //change to test
	int rotateRightTest = rotateRight(test3, 7, 6);
	cout << "The array has been reset and rotated right. The test returns: " << rotateRightTest << endl;
	for (int k = 0; k < 10; k++) // gives each value in the array
		cout << "The " << (k + 1) << "th term in the array is now: " << test3[k] << endl;

	//FLIP TEST
	string test4[10] = {"Joe", "Bob", "Frank", "John", "Mary", "Elizabeth", "Amanda", "Zach", "Bill", "Malisa"}; //change to test
	int flipTest = flip(test4, 4);
	cout << "The array has been reset again and flipped. The test returns: " << flipTest << endl;
	for (int k = 0; k < 10; k++) // gives each value in the array
		cout << "The " << (k + 1) << "th term in the array is now: " << test4[k] << endl;

	//DIFFER TEST
	string test5[10] = {"Joe", "Bob", "Frank", "John", "Mary", "Elizabeth", "Amanda", "Zach", "Bill", "Malisa" };
	string test6[8] = {"Joe", "Bob", "Frank", "John", "Mary", "Elizabeth", "Amanda", "Zach"}; //change to test
	int differTest = differ(test5, 10, test6, 8);
	cout << "The array has been reset. This time it is being compared to another array \n that is slightly different. The test returns: ";
	cout << differTest << endl;

	//SUBSEQUENCE TEST
	string test7[3] = {"Bob", "Frank", "John"}; //change to test
	int subsequenceTest = subsequence(test5, 10, test7, 3);
	cout << "The array is being searched for a subsequence. Subsequence test returns: " << subsequenceTest << endl;

	//LOOKUPANY TEST
	string test8[6] = {"Marvin", "Johnson", "Zach", "Joanna", "Doug", "Harry"}; //change to test
	int lookupAnyTest = lookupAny(test5, 10, test8, 6);
	cout << "The first term in the array in common with the test string is: " << lookupAnyTest << endl;

	//SPLIT TEST
	string splitString = "Bob"; //change to test
	int splitTest = split(test5, 10, splitString); //uses the first array from differ test
	cout << "Splitting the array using string " << splitString << ":" << endl;
	for (int k = 0; k < 10; k++) // gives each value in the array
		cout << "The " << (k + 1) << "th term in the array is now: " << test5[k] << endl;
	cout << "The function returns: " << splitTest << endl;

}

