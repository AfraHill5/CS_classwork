//Pointer notes

//you can think of the computer's memory like a street with a bunch of vacant lots
//when variables are defined the compiler finds an unused address in memory and reserves it
//the address of a variable is defined to be the first address in memory where the variable is stored
//you get the address of a variable using the & operator.

int main()
{
	int vomit = 15;
	char booger = 'B';
	cout << "vomit's address" << &vomit << endl;
	cout << "booger's address" << &booger << endl;
}
//this would output the addresses of the 2 variables, usually in hex

//you save the addresses of variables using a pointer variable. a pointer variable is a variable that holds
//an address rather than an int/float/double/etc
//an address is just a number. it holds data just like an int would hold data

//a pointer will always be the same size regardless of what its pointing to, because its only purpose is to hold the value
//of an address in memory. it doesn't matter what it is pointing to, it will always be the same size in memory

int main()
{
	short Jennifer;
	short* blackBook;
	
	blackBook = &Jennifer;
}

//you have to specify what type of data is being pointed to so C++ knows what to do with it.

int main()
{
	float diarrhea = 3.1415;
	float *ptr;
	
	ptr = &diarrhea;
	
	string barf = "blah";
	string *ptrToStr;
	
	ptrToStr = &barf;
	
	int eek;
	int *ptr, *ptr2;
	
	ptr1 = &eek;
	ptr2 = ptr1; //both point to eek
}

//Once you have a pointer you can use it to modify the variable being pointed.

int main()
{
	short Jennifer;
	short* blackBook;
	
	blackBook = &Jennifer; //now points to Jennifer
	*blackBook = 5; //Jennifer now = 5
}

//if you initialize a pointer and try to follow it without pointing it somewhere first, it will produce
//undefined behavior -- but it will still compile, so be careful. sometimes the compiler will produce warnings.

//what do you use the * operator for? to modify a variable defined in another function.

void set(int pa)
{
	pa = 5;
}

int main()
{
	int x = 1;
	set(x);
	cout << x;
}
//x still = 1!
//you need to use pointers to solve this

void set(int* pa)
{
	*pa = 5;
}

int main()
{
	int x = 1;
	set(&x);
	cout << x;
}
//this time x = 5.

//when you pass a variable to a function by reference, you are really just using a pointer.
//the above is the same as this

void set(int &val)
{
	val = 5;
}

int main()
{
	int x = 1;
	set(x);
	cout << x; //5
}

//write a swap function that accepts 2 pointers to ints and swaps the 2 values pointed to by the pointers

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//pointer arithmatic can be used to traverse arrays. when you pass an array to a function, you are really passing
//the address of the start of the array

void printData(int array[])
{
	cout << array[0] << "\n";
	cout << array[1] << "\n";
}

int main()
{
	int nums[3] = {10, 20, 30};
	
	printData(nums); //prints 10 20
	printData(&nums[1]); //prints the address of 20
	//these lines do the same thing
	printData(nums+1); //prints 20 30
	printData(nums[1]); //      20 30
}

//you can also use pointers to access the fields of a structure.

struct Car
{
	char name[6];
	int hp;
	int doors;
};

int main()
{
	Car c1;
	Car* p1;
	
	pt = &c1;
	
	(*p1).hp = 140; //sets the hp in c1 to 140
	(*p1).doors = 2; //sets the number of doors in c1 to 2
	strcpy((*p1).name, "Jeep");
}

//shorthand version that works the same:
int main()
{
	Car c1;
	Car* p1;
	
	pt = &c1;
	//shorthand
	p1->hp = 140;
	p1->doors = 2;
	strcpy(p1->name, "Jeep");
}

//dynamic allocation

int main()
{
	int *arr;
	int size;
	cin >> size;
	
	arr = new int[size];
	
	arr[0] = 10;
	arr[2] = 75;
	
	delete [] arr; //weird syntax, use this to delete arrays ("delete ptr" otherwise)
	//at this point you can't use arr anymore -- it points to undefined memory
}

//you could use new and delete within a class as well. ex

class MathProf
{
	public:
		MathProf(int n)
		{	
			m_n = n;
			m_arr = new int[n];
			for (int j = 0; j < n; j++)
				m_arr[j] = j*j;
		}
		~MathProf
		{
			delete [] m_arr;
		}
	
	private:
		int *m_arr, m_n;
}

