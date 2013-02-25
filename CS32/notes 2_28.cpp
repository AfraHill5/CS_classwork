//Notes 2/28

//continuing from last lecture
//a function to print every member of a tree
void printTree(Node* p)
{
	if (p != NULL)
	{	
		cout << p->name << endl;
		for (int k = 0; k < p->children.size(); k++)
			printTree(children[k]);
	}
}

//This works, but what if we wanted to print out the lower branches with indents based on their depths?
//It would make the output more readable. You would do it this way:

void printTreeAuxiliary(Node* p, int depth)
{
	if (p != NULL)
	{
		cout << string(2*depth, ' ') << p->name << endl;
		for (int k = 0; k < p->children.size(); k++)
			printTreeAuxiliary(children[k]);
	}
}

void printTree(Node* p)
{
	printTreeAuxiliary(p, 0);
}

//A Binary Tree is either 1. empty or 2. a node with a left binary subtree and a right binary subtree.
/* 			O
		  /   \
		 O     O
	    / \   / \
	   O   O O   O 
	       etc.			*/
//It's actually possible to represent any tree as a binary tree.

//A binary search tree (BST) is either 1.empty, or 2. a node with a left BST such that the value of every item in that subtree is
//<= the value at the node, and a right BST such that the value of every item in that subtree is >= the value at the node.

void print(Node* p)
{
	if (p != NULL)
	{
		print(p->left);
		cout << p->name << endl;
		print(p->right);
	}
}

//This would print a sorted array in alphabetical order.

//Binary search trees can work well when they are balanced, but unbalanced, nearly linear trees are not very efficient -- they approach O(N) speed.
//Creating the tree efficiently vastly adds to its usability and speed.

//The trick is to order the inputs before putting them into a tree structure, so they are spread out instead of put in a "line" structure. A lot of 
//algorithms will sort the input into alphabetical order before sending the information to the tree algorithm, but this is the worst possible result --
//in this case, the tree will just be one string going all the way down, and will approach O(N).
//The best case scenario is a O(logn) behavior, but this only happens if the tree is well balanced. 


