//Notes 2/23

//Review: O(N^2) sorts:
//	selection sort
//	bubble sort
//	insertion sort
//O(NlogN) sort
//	mergesort

//Another sort is called the "quicksort":
5 3 7 6 1 8 2 4
//Choose a "pivot" -- the easiest case is the first value, 5.
//Then apply this logic: step through the array. if the value is greater than the pivot, do nothing; if it is less than the pivot,
//put it in front of the pivot and shift everything else down.
//We end up with this:
1 3 4 2 *5* 8 6 7
//Now we call the function recursively, using all the values in front of the pivot, and all the values behind the pivot.
//The base case is 2 values -- if they are in order, return; if they are not, swap and return.
 
 //This is an O(NlogN) sort, and has a better constant of proportionality than mergesort. So far it is the fastest sort algorithm we have seen
 // for the average case, but there are definitely downsides. The worst case is noticibly slower than mergesort's worst case -- in fact, it approaches
 // O(N^2)! To avoid this worst case, people started changing the function in order to guarantee a higher minimum speed.
 
 //For example, instead of just taking the first value as the pivot (cheap, but not efficient -- can lead to worst case behavior) or first finding the median
 //value and using it as a pivot (expensive), you can just find the median value of a few select numbers in the array (usually 3 -- the first, last, and middle),
// and hope the array has a general distribution so the average is about the same. It turns out to be quite cheap, and surprisingly efficient.
// This behavior reduces the worst case by a noticible margin. 

//This algorithm is "smart" -- it monitors its own behavior, and if it sees that it is going down a path that will lead to worst case (O(N^2)) behavior, it
//switches to mergesort (worst case O(NlogN)) for the rest of the values. Generally this behavior occurs at recursion depth 2logN.
//This is called "introsort" and is generally considered the current cutting-edge sorting algorithm.

------------------------------------------------------------

//Trees
/* 				A
			  /   \
			 B     C
		    / \   / \
		   D   E F   G
				etc.
The topmost class is called the root, and the furthest-down classes are called leaves. In-betweens are called branches.
Oftentimes people will reference "interior" vs "leaf" nodes, or "parent" vs "child" nodes.
Trees are interesting because there is a unique path to each and every leaf on the tree. 		*/

//You could represent a node object as so:
struct Node
{
	string name;
	vector<Node*> children; //recall a dynamically resizable array is called a vector.
};
Node* root;

//How would we count the number of elements in a tree?
int count(Node* p)
{
	int n = 1;
	for (int i = 0; i < p->children.size(); i++)
		n += count(p->children[i]);
	return n;
}
//Recursion and trees go hand in hand, because it's the easiest way to deal with lots of different-sized objects.