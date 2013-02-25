/*write a function int shifts_are_arithmatic that yields 1 when run on a machine
that uses arithmatic right shifts for ints and 0 otherwise. */


#include <stdio.h>

int int_shifts_are_arithmatic()
{
	int test = -1; /*-1 = 1..1 on all machines running 2s complement */
	test = test >> 1; /*shifts to the right 1 bit */
	unsigned char* testPtr = &test;
	/* this ptr should point to a 0 if the shift was not arithmatic as it pts
	   to the first bit in the integer. if it was arithmatic, it 
	   will pt to a 1 because it was the leading bit */

	if (*(testPtr) == '0')
		return 0;
	else
		return 1;
}
