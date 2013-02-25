/* original, buggy code: */

void copy_int(int val, void *buf, int maxbytes)
{
	if (maxbytes-sizeof(val) >= 0)
		memcpy(buf, (void*) &val, sizeof(val));
}



/*
	This code doesn't work because sizeof() returns an unsigned integer. 
	Maxbytes is implicitly cast to be unsigned, and subtracting an unsigned
	number from another can never give a value less than 0. The if statement
	will therefore always be triggered.
*/

/* If you use signed subtraction, the if statement will work because it 
	will be able to represent negative numbers. 	*/


void copy_int_fixed(int val, void *buf, int maxbytes)
{
	if((signed) maxbytes - sizeof(val) >= 0) 
		memcpy(buf, (void*) &val, sizeof(val));
}


