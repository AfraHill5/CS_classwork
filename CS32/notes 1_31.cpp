//Notes 1/31/2011

class Shape
{
  public:
	virtual void move(-,-);
	virtual void draw() const = 0; 
   ...
};
//the virtual keyword tells the compiler to use the subclass implementation if it exists, and the Shape implementation
//if it does not. setting it = to 0 makes it an abstract class -- you can't create a Shape object on its own because it has no 
//implementation for the draw function. This means the compiler will automatically use the subclass implementation every time.


class Circle : public Shape
{
  public:
	virtual draw() const;
...
};

void f(Shape& s)
{
	s.move(10,20);
	s.draw();
}

Circle c;
f(c);

//As soon as you start making functions = 0 you create an abstract class, meaning you can't directly create that type of object, 
//only a subclass of it. We cannot create Shapes, but we can make Circles, Rectangles, etc. and in this example it makes
//sense because there is no reason to create a Shape and not a subclass of it.

//Once a class is introduced as virtual in an overclass, it will be virtual all the way down through all children/grandchildren/etc. regardless of whether
//it is declared as such each time.

//Say we were working on an algorithm to sort a pile of N items. Our example logic would be as follows:
/*	Split the pile into 2 piles of (N/2) items each
	sort the left subpile
	sort the right subpile
	merge the two sorted subpiles   */
	
//This is called a recursive solution because the subproblem that you are trying to solve is simply a smaller instance of the larger problem.
//This is not, however, an infinite loop because each time you have to sort the items, you have less items to deal with. Eventually the problem will be
//small enough to solve immediately.

//In this case we would know how to "solve" the sort immediately if there was only 1 item in the pile. At this point te recursive solution becomes redundant --
//it is ridiculous to try to sort a pile of 1 item by splitting it into 2 seperate piles. Thus we must recognize when the pile reaches that 
//size and stop dividing the pile further. We should change the algorithm to only split the pile if N > 1.

//Reaching the end of a recursive function is called the Base case, and the recursive case is the situation where we have to split the problem up further.

//Lets test this using an array of integers we can sort.
/*
arr ________________________
   |    |    |    |    |    |
   | 40 | 20 | 50 | 10 | 30 |
   |____|____|____|____|____|
We need to sort this array so that it is in order (10, 20, 30, 40, 50).  */

void sort (int a[], int b, int e) //uses pointers to "split up" the array using the recursive logic from above
{
	if (e - b > 1) //if there is more than one item in the portion of the array that you are sorting (b points to front, e to back)
	{
		int mid = (b+e) / 2 //takes the average of b and e using integer division (finds the midpoint)
		/*
			     ________________________
				|    |    |    |    |    |
			b->	| 40 | 20 | 50 | 10 | 30 |	<-e
				|____|____|____|____|____|
							^
							mid
		*/
		sort(a, b, mid);
		sort(a, mid, e); //the function calls itself again.
		merge(a, b, mid, e); //when all subdivisions are sorted, merges them all together.
	}			
}	

sort(arr, 0, 5);

//this will successfully sort the array into (10,20,30,40,50).

//This is the power of recursion -- it is very compact, easy to check, and works quickly.
