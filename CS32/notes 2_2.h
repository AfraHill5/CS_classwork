//Notes 2/4
//Recursive function to caluculate fibonacci sequence
f(int n)
{
if (n == 0 || n == 1)
	return 1;
return f(n-1) + f(n-2);
}
//This works but creates a tree with height n and width (2^n). This can be trouble if n is a large value and creates a massive memory load.

