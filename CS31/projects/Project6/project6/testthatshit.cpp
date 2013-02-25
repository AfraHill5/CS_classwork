//Zach North
//603 885 768
//Project 6 Testing
#include <iostream>
#include <string>
using namespace std;

//Problem 1
//1a
/*  int main()
    {
        int arr[3] = { 5, 10, 15 };
        int* ptr = arr;

        *ptr = 10;
        *(ptr + 1) = 20;
        ptr += 2;
        ptr[0] = 30;

        for (int k = 0; k < 3; k++)
			cout << *(arr + k) << endl;
    }   */


//1b
/* void findMax(int arr[], int n, int* &pToMax)
{
	if (n <= 0) 
		return;      // no items, no maximum!
    
	int max = arr[0]; //sets the max to the first array element
	pToMax = &arr[0]; //points to the address of the first array element

	for (int i = 1; i < n; i++) //steps through array looking for highest value
	{
		if (arr[i] > max) //if the array element is bigger than the current max
		{
			max = arr[i]; //the new max is the current array element
			pToMax = &(arr[i]); //pToMax points to the new max in the array
		}
	}
}       

int main() //cannot be changed
{
	int nums[4] = { 5, 3, 15, 6 };
	int* ptr = NULL;
	findMax(nums, 4, ptr);
	cout << "The maximum is at address " << ptr << endl;
	cout << "It's at index " << ptr - nums << endl;
	cout << "Its value is " << *ptr << endl;
} */

//1c
/*void computeCube(int n, int* ncubed)
{
	*ncubed = n * n * n;
}

int main()
{
	int* ptr;
	int n;
	ptr = &n;
	computeCube(5, ptr);
	cout << "Five cubed is " << *ptr << endl;
} */


//1d

// return true if two C strings are equal
 /*bool strequal(const char str1[], const char str2[])
{
	while (*str1 != '\0'  &&  *str2 != '\0')
	{
		if (*str1 == *str2) //if the 2 chars are equal
		{
			cout << "trigger";
			str1++;            // advance to the next character
			str2++;
		}
		else
			return false;
	}
	return true; 
}

int main()
{
	char a[10] = "pointed";
	char b[10] = "pointer";

	if (strequal(a,b))
		cout << "They're the same!\n"; 
}
*/

//1e
   /* int* getPtrToArray(int& m)
    {
        int anArray[5] = { 5, 4, 3, 2, 1 };
        m = 5;
        return anArray;
    }

    void f()
    {
        int junk[100];
        for (int k = 0; k < 100; k++)
            junk[k] = 123400000 + k;
    }

    int main()
    {
        int n;
        int* ptr = getPtrToArray(n);
        f();
        for (int i = 0; i < n; i++)
            cout << *(ptr + i) << ' ';
    } */


//2
/*int main()
{
	//A
	double * scoop;
	
	//B
	double vanilla[5];

	//C
	scoop = &vanilla[4];

	//D
	*scoop = 17;

	//E
	*(vanilla + 3) = 42;

	//F
	scoop -= 3;

	//G
	scoop[1] = 33;

	//H
	scoop[0] = 25;

	//I
	bool b = (*scoop == *(scoop + 1));

	//J
	bool d = (scoop == vanilla); 
} */

//3a
/* double computeMean(const double* scores, int numScores)
{
	const double* ptr = scores;
	double tot = 0;
	while (ptr != scores + numScores)
	{
		tot += *ptr;
		ptr++;
	}
	return tot/numScores;
}

double computeMean2(const double* scores, int numScores)
{
	const double* ptr = scores;
	double tot = 0;
	for (int k = 0; k < numScores; k++)
		tot += *(ptr + k);
	return tot/numScores;
} */

//3b
// This function searches through str for the character chr.
// If the chr is found, it returns a pointer into str where
// the character was first found, otherwise NULL (not found).

/* const char* findTheChar(const char str[], char chr)
{
	for (int k = 0; *(str + k) != 0; k++)
		if (*(str + k) == chr)
			return (str + k);
	return NULL;
} */

//3c
/* const char* findTheChar(const char str[], char chr)
{
	if (*str == chr)
		return str;
	else
		str++;
	if (*str == '\0')
		return NULL;
} */

//4
    /* #include <iostream>
    using namespace std;

    int* maxwell(int* a, int* b)
    {
        if (*a > *b)
            return a;
        else
            return b;
    }

    void swap1(int* a, int* b)
    {
        int* temp = a;
        a = b;
        b = temp;
    }

    void swap2(int* a, int* b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

    int main()
    {
        int array[6] = { 5, 3, 4, 17, 22, 19 };

        int* ptr = maxwell(array, &array[2]);
        *ptr = -1;
        ptr += 2;
        ptr[1] = 9;
        *(array+1) = 79;

        cout << &array[5] - ptr << endl;

        swap1(&array[0], &array[1]);
        swap2(array, &array[2]);

        for (int i = 0; i < 6; i++)
            cout << array[i] << endl;
    } 
	*/

//5

void removeS(char* ptr)
{
	while (*ptr != '\0')
	{
		if (*ptr == 's' || *ptr == 'S')
		{
			char* temp = ptr;
			for(;;)
			{
				*ptr = *(ptr + 1);
				ptr++;
				if (*ptr == '\0')
				{
					ptr = temp;
					break;
				}
			}
		}
		else
			ptr++;
	}
}

int main()
{
	char msg[50] = "She'll be a massless princess.";
	removeS(msg);
	cout << msg;  // prints   he'll be a male prince.
}
