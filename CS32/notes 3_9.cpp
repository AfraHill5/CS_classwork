//Notes 3/9
//a heap is like a "magic bag" that automatically sorts the inside items for you. we could utilize this using a form of "heapsort"
//1. make an array a heap
//2. successively remove each item.

//The simplest way to make a binary tree a heap is to start from the bottom and work your way up. You don't have to worry about the leaf nodes because
//they are already heaps -- they have no values below them to sort. Start with the first level of branches. If the branch is smaller than one of its
//children, swap them. The biggest should be on top, with 2 smaller below it. Keep doing this up to the top of the tree.
//To convert a complete binary tree into a heap is O(nlogn) complexity.

//Now we remove the root from the tree, return it as the largest value, and promote the bottom-right-most element of the tree to the top.
//Reform the heap, return the root, and do this again until no elements remain. Now the returned value contains all the original values and has been returned 
//in order.

//Heapsort requires random-access - great if you want to sort a vector or an array, but not so great on a linked list.
//Mergesort can be used on linked lists, so generally heapsort = vectors/arrays, mergesort = linked lists.

//Introsort is a modification that automatically finds the fastest of the two, and runs it. Currently the "cutting edge" of sorting algorithms.

//A whole library of graph algorithms exists, and you can solve your problems much faster if you can visualize them in the form of a graph because just
//about every possible function dealing with graphs has been written already. Graphs are defined by nodes/vertices, edges, and paths -- edges connect
//nodes, and paths traverse multiple edges to get between 2 endpoints.

//Graphs with "cycles" are called cyclic; this means that multiple nodes point to each other in a circular structure. A graph representing the prerequisite
//structure for getting through UCLA, for example, would not want cycles because it would not make any sense; thus we would want what is called a directed
//acyclical graph (no cycles, and it all points in the same direction.) A graph of city streets may not care about cycles and thus a cyclical graph would
//be OK.

//Certain graph problems just turn into matrix operations -- for example, if you made a table of distances between each node (an adjacency matrix) you
//could perform operations on this matrix using linear algebra. 

//General steps of engineering process
//1. Requirements analysis -- find out what product is wanted / needed by the user
//2. Risk analysis -- is it worth undetaking the project? Cost/benefit/profits?
//3. Analysis -- what must be done? What do we have to do to make the project happen?
//4. Design -- how will it be done?
//5. Implementation -- implement the design.
//6. Testing -- find problems.
//7. Deployment -- deliver the project to users.
//8. Maintenance and enhancement -- deal with problems encountered by uses, or add features.



