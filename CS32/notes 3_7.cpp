//Notes 3/7
//Hash tables

//the main idea of hash tables is to have some number of "buckets", similar to a huge array, and a function to transform each input into a bucket "key"
//or coordinate. This key must be cheap and non-random; that is, it gives the same value every time for the same input.

//The key function must be quick, or you lose the benefit of using hash tables (speed.) It also must produce a fairly uniform distribution among the buckets,
//and be able to deal with "collisions" (the same address produced for seperate inputs.) 

//The table must be much greater than the number of units to be inserted (at least twice as big.) The idea is you run each input through the hash function,
//generate an address for the input and map it there in the array. In case of collisions, the input is placed in the next available slot. This is called a
//CLOSED HASH TABLE, and it has a couple advantages, but the main disadvantage is the collision problem -- it's annoying and confusing to move all the
//elements around, and in cases of "clustering" can become very expensive if you need to track down the table just looking for an open space.

//A much easier type of structure is the OPEN HASH TABLE. The array of buckets simply becomes a singly linked list rather than an array. When an item hashes
//to a value, it is simply inserted into the list in the spot indicated. "Collisions" aren't really a problem, because you can just insert another list
//element and hook up the pointers.

//A hash table with a fixed number of buckets have an O(N) search complexity, which seems like a lot (binary search trees are O(nlogn)); however, it has an
//extremely small constant of proportionality, so it ends up being faster.

//There is also a concept of the load factor of a hash table (# of items in the table / # of buckets in the table). In general, if hash tables get too big 
// (load factor > 0.4 or so) you'd like to increase the number of buckets. This is more relevant to the closed table than the open one in terms of performance.

//Hash functions are fairly simple -- they convert an input value to a simple integer. Then you take the int % #buckets to find the address for the hash.
//If you need more buckets, just do a "rehash" -- make a new set of buckets twice the size and re-modulo all the integer values to get new addresses for the 
//new table.

//Hash table operations are called "amartized constant time" -- that is, if you allow dynamic resizing of the table size, they can essentially approach
//constant time (very efficient.) So what's the advantage of a binary search tree? Binary search trees let you visit every item in order rather than at 
//random, which can be used for a lot of operations. Another problem is the rehash operation is not conducive to real-time response applications -- they tend to 
//freeze up for a couple of seconds before continuing, which you may not be able to afford in time-sensitive operations.

//the FNV algorithm: take some big number, then add each character in the string's ASCII value to the big number, and then multiply by some other big integer.
//You then used this number and % by number of buckets to get the key for the item location. Fairly straightforward and easy to implement, and this algorithm
//gives you a pretty good distribution.

//HEAP -- a data structure ideal for so-called "priority queues" or queues different than "first-in, first-out." A (max) heap is a complete binary
//tree where the value at every node is >= the values in its subtrees. (Min heap ->  <=) Inserting a value first puts the new value in its correct place
//in a complete binary tree and then "bubbles it up" until it is in the correct value (swaps places up the tree with its parents until its in the 
//right place.)

//A heap has time-complexity O(logn) for insert.

