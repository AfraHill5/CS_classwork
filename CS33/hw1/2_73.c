/* 
	Write code for a function with the following prototype:
*/

#include <limits.h>
#include <stdio.h>


int saturating_add(int x, int y)

/*
	Instead of overflowing the way normal 2s-complement addition does, 
	saturating addition returns TMax when there would be positive overflow
	and TMin when there would be negative overflow. Saturating arithmatic
	is commonly used in programs that perform digital signal processing.
*/

{
	int result = x + y; 
	
	int signChecker = INT_MIN; /*1000...; used to check for +/- */
	int isPositiveOverflow =(  ~(x      & signChecker)  /*x >= 0 */
				 & ~(y      & signChecker)  /*y >= 0 */
			         &  (result & signChecker));/*result < 0 */
		 /*keeps track of whether + overflow or not */

	int isNegativeOverflow = (  (x      & signChecker) /*x < 0*/
				 &  (y	    & signChecker) /*y < 0*/
				 & ~(result & signChecker)); /*result >= 0 */
		/*keeps track of whether - overflow or not */


	int shiftAmt = ((sizeof(int)) << 3) - 1;

	isPositiveOverflow = (isPositiveOverflow >> shiftAmt);
	isNegativeOverflow = (isNegativeOverflow >> shiftAmt);

	/*here we exploit the guaranteed arithmatic shift to turn the two
	overflow integers into either 000..0 or 111..1. By doing this we can
	& them with our numbers to determine whether or not an overflow occured
	*/

	/* isPositiveOverflow is  11..1 if x and y are positive numbers, but 
	   the result is negative; otherwise it is 00..0. isNegativeOverflow
	  is 1 if x and y are negative numbers but the result is positive. */

	return ((INT_MAX & isPositiveOverflow) + (INT_MIN & isNegativeOverflow)
		+ ( ((~isPositiveOverflow) & (~isNegativeOverflow)) & result ) );

	/*we return 
		- INT_MAX if it overflowed positively
		- INT_MIN if it overflowed negatively
		- the result if it did not overflow at all  
	*/
}
