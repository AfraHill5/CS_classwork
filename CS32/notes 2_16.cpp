//Notes 2/16/2011

//A set is a collection of items that does not allow duplicates, optimized for quick lookup.
// It can be found in the STL

set<int> si;
si.insert(10);
si.insert(30);
si.insert(10);
cout << si.size() << endl; //2

//There is also a multiset that does allow duplicates -- it's basically the Bag function from the HW

multiset<int> mi;
...


//algorithm relative efficiencies -- performance differences
for (int i = 0; i < N; i++)
{
	a[i] *= 2;
} //doubles every item in the array

//what about
a[i] = a[i] + a[i];
//Is this way faster, or slower than the above?

//well in this case we don't really care, because the performace difference is so slow. However, the question is 
//still valid, because we need to know the fastest way to do things a lot of the time.

//What really matters in this case is the N value -- how many basic steps are there to be run?
//There is a mathematical notation used in algorithm analysis -- "f(n) is O(n) [order n]"
//Basically this says that f(n) is bounded above by some constant function of N.
//This is telling you that if you try to evaluate f(n) for an N twice as big, f(n) will be roughly twice as big.

//ex: if you have 1000 items to search through and it takes n time, if you look through 2000 items it will take roughly
//    twice as long.

//If you'd like, you can split up the analysis into "best case", "worst case" and "avg case." For example, searching for N
//items looks at "best case": 1 item, "worst case": n items, "avg case": n/2 items.

//Real world applications look at the "worst case": this program must return in, at worst, n seconds. etc.

//linear search : O(n) or linear time.
//binary search : O(log_2_(n)) or takes time proportional to log_2_n.

//linear search:
/*
ITEMS		AVG			WORST
10^3		500			10^2
10^6		5x10^5		10^6
10^10		5x10^9		10^10

//binary search:
ITEMS		AVG			WORST
10^3		9			10
10^6		20			25
10^9		30			30				*/

//basically this lets you see the radical difference different algorithms can have when looking at high n values.

//Because all logs are proportional to one another, people will often right the order of binary search as "O(log(n))".

//To recap:
//Some algorithms, such as accessing a value in an array, take the same amount of time no matter how many elements
//have to be searched. We call these "constant time" algorithms or O(1) algorithms.
//Some algorithms make exactly n passes through an array. We call these "linear time" algorithms or O(n).
//Then of course there is the "log time" algorithms or O(log(n)).

//What about a multi-dimensional array traversal?
for(int i = 0; i < N; i++)
{
	for (int j = 0; j < N; j++)
	{
		c[i][j] = a[i][j] + b[i][j];
	}
}

//How many times does the inner loop run? N times
//Outer loop? N times
//This would then be called an O(n^2) problem. If you doubled the size of N, this would take 4x as long to run.

//How about a more complicated traversal:
for (int i = 0; i < N; i++)
{
	for (int j = 0; j <= i; j++)
	{
		K( c[i][j] = a[i][j] + b[i][j]; )
	}
}

//This comes out to about .5Kn^2, which is still O(n^2). It still grows on the n^2 scale, regardless of all the other
//confusing details.

//Others: traditional matrix multiplication =   O(n^3)
//		  optimized matrix multiplication =     O(n^2.4)
//		  others: 								O(nlog(n))

//A couple common sortin algorithms (some are very good, some incredibly bad):

| 5 3 7 6 1 8 2 4 //find the lowest value and put it in first position. swap first position with lowest, and increment the first position pointer.
1 | 3 7 6 5 8 2 4
1 2 | 7 6 5 8 3 4 
1 2 3 | 6 5 8 7 4
1 2 3 4 | 5 8 7 6
1 2 3 4 5 | 8 7 6
1 2 3 4 5 6 | 7 8 
1 2 3 4 5 6 7 | 8
1 2 3 4 5 6 7 8 |

//Each pass through the array puts one more item into the correct place.
//This algorithm is called "selection sort." It requires n + (n-1) + (n-2) + (n-3) + ... + 2 steps, or about
//.5n^2 steps. In other words, this is an O(n^2) sorting algorithm.
//This algorithm kinda sucks -- it is inefficient and is difficult to get any information on each "pass" other than
//which item is the smallest. What if you want to know the biggest? Second biggest? You have to sort the whole array
//first.

5 3 7 6 1 8 2 4 | //look at neighbor to the right -- if the item to the right is smaller than the current one, swap the two.
3 5 6 1 7 2 4 | 8 //the 8 has already reached the proper place, so don't have to check it again
3 5 1 6 2 4 | 7 8 //now the 7 has gravitated to the end.
3 1 5 2 4 | 6 7 8
1 3 2 4 | 5 6 7 8
1 2 3 | 4 5 6 7 8 //since we can make it through a pass without making a swap, we can stop.

//This is called the "bubble sort" algorithm because the high values "float" to the top like bubbles.
//It potentially looks a little better than selection sort, partly because it can finish early -- its best case is better.
//However, its still an O(n^2) sort. And thus, it's pretty bad.

5 | 3 7 6 1 8 2 4 //look at the first element on the right of the barrier and insert it to the left where it belongs.
3 5 | 7 6 1 8 2 4
3 5 7 | 6 1 8 2 4
3 5 6 7 | 1 8 2 4
1 3 5 6 7 | 8 2 4
1 3 5 6 7 8 | 2 4
1 2 3 5 6 7 8 | 4
1 2 3 4 5 6 7 8 |

//The advantage to the "insertion sort" method is that if you get lucky, you don't have to do many steps to search
//through the left side of the barrier. If the value to be inserted is higher than all the left side, you don't have to do
//any steps at all. Thus this algorithm has a very good best case. On average, though, you have to examine half of the 
//left side to find the correct spot for the insertion.
//Ultimately this is a better algorithm than the above two, but it still comes out to around .25n^2 -- still an
//O(n^2) sort, but with a much better upside and it is very easy to code.

//Recall our mergesort recursive sort:
if (N >= 2)
{
	sort the left half;
	sort the right half;
	merge;
}

//We already know that the merge step itself already is an O(N) order -- it requires you to step through all the items.
//Also, time to do the whole function = time to sort N/2 items, twice, + N(merge).
//T(N) = 2T(N/2) + N
//Smallberg claims the answer is nlog(n).
//2T(N/2) + N = 2(N/2)(Log_2_(N/2)) + N
// 			  = N log_2_N

//So this sorting algorithm is O(Nlog(N))! Thus it is much more efficient than all the other algorithms we have looked at so far.
//The difference between using an NlogN sort and an N^2 sort is massive! It can save you a ton of time (7 hrs vs. 15 minutes.)

