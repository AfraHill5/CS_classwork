//Notes 2/14
//Reviewing templates

template<typename T>
T minimum(const T& a, const T& b)
{
	if (a < b)
		return a;
	else
		return b;
}

//This takes any 2 inputs, as long as they are the same, and compares them to find the minimum.
//This is the power of a template object -- allows you to write much less code 

template<typename T>
T sum(const T a[], int n)
{
	T total = 0;
	for (int k = 0; k < n; k++)
		total += a[k];
	return total;
}
//Why does this not work? You can't initialize a lot of datatypes to 0 -- for example, initializing "string"
//to 0 would produce an error / you wouldn't get the empty string like you want.
//If you want to initialize a datatype to be "empty", you can do this:
template<typename T>
T sum(const T a[], int n)
{
	T total = T();
	...
}
//Just tell the template to call the T's default constructor, and the compiler will figure out you want an
//empty version of the inputted datatype -- even if it is an int or double, or another type without a constructor.


template<typename T>
class Stack
{
public:
	Stack();
	void push(const T& x);
	void pop();
	T top() const;
	int size() const;
private:
	T m_data[100];
	int m_top;
}

template <typename T>
Stack<T>::Stack()
 : m_top(0)
{}
 
template<typename T>
void Stack<T>::push(const T& x)
{
	m_data[m_top] = x;
	m_top++;
}

...

//This represents the basic syntax to create a template class and templatized implementations for its member
//functions. It is much simpler to create template classes when you may be using it for multiple datatypes
//because it allows you to only write the class once, rather than a bunch of times.

//Be careful though -- any clas you call a template with must be 1. assignable and 2. have a default constructor.
//You also can't call the function with a datatype of itself (no recursive classes :])

//There exists a Standard Template Library (STL) that basically contains a massive library of templates for
//linked lists, stacks, etc. After this class you will probably never have to write code for any of these things
//again, you can just use the STL versions and save a ton of time.

//some stl templates include: vector (dynamically resizable array)
#include <vector>
using namespace std;

vector<int> vi;
vi.push_back(10); //stores the number in the back of the array
vi.push_back(20);
vi.push_back(30); 
//10 20 30
cout << vi.size(); //writes 3
cout << vi.front(); //writes 10
cout << vi.back(); //writes 30
vi[1] = 40;
//second value
for (size_t k = 0; k < vi.size(); k++)
	cout << vi[k] << endl; //writes 10 40 30
vi.pop_back();
for (size_t k = 0; k < vi.size(); k++)
	cout << vi[k] << endl; //writes 10 40 
vi.at(1) = 60;
vi.at(3) = 70; //throws an exception.
vector<double> vd(10);
//vd.size() == 10, each element is 0.0
vectir<string> vs(10, "Hello")
//vd.size() == 10, each element is "Hello"
int a[5] = { 10, 20, 30, 40, 50 }
vector<int> vx(a, a+5);
//vx.size() is 5, vx[0] is 10, vx[1] is 20, ... vx[4] is 50

#include <list>
using namespace std;

list<int> li;
li.push_back(20);
li.push_back(30);
li.push_front(10);
cout << li.size(); //writes 3
cout << li.front(); //writes 10
cout << li.back(); //writes 30
li.push_front(40);
li.pop_front();

li.begin()                               li.end()
   V                                       V
   10            20            30 
   
for (list<int>::iterator p = li.begin(); p != li.end(); p++)
	cout << *p << endl;
//writes 10 20 30, one per line

//An iterator is a special pointer that points to list elements. You use the * operator before it to reference
//the value inside the list node it is pointing to, and the ++ operator moves it to the next node in the list.

template<typename Q, typename T>
Q find (Q b, Q e, const T& target)
{
	for ( ; b != e; b++)
		if (b* == target)
			break;
	return b;
}

int main() 
{
	int a[5] = { 10, 50, 40, 20, 30 }
	int k;
	cin >> k;
	int* p = find (a, a+5, k);
	if (p == a+5)
		...not found
	else
		...found, p points to the first value with that value
		
	list<string> ls;
	...
	list<string>::iterator q = find(ls.begin(), ls.end(), "Fred");
	if (q == ls.end())
		...not found...
	...
	
	vector<int> vi;
	...
	vector<int>::iterator r = find(vi.begin(), vi.begin() + 5, 42)
	if (r == vi.begin() + 5)
		...not found...
}

//you can also use the find_if function to find the first element that satisfies some condition (negative, empty, etc.)
//to do this, you utilize pointers to functions.

template<typename Iter, typename func>
Iter find_if(Iter b, Iter e, Func f)
{
	for ( ; b != e; b++)
		if(f(*b))
			break;
	return b;
}

bool isNegative(int k)
{
	return (k < 0);
}

bool isEmpty(string s)
{
	return (s.empty());
}		

int main()
{
	vector<int> vi;
	...
	vector<int>::iterator p = find_if(vi.begin(), vi.end(), isNegative); //passes the isNegative function as a pointer to the template
	if (p == vi.end());
		...not found...
		
	list<string> ls;
	...
	list<string>::iterator q = find_if(ls.begin(), ls.end(), isEmpty);
	...
}

