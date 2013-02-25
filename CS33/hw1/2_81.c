
/*sample code*/

int main()
{
	int x = random();
	int y = random();
	unsigned ux = (unsigned) x;
	unsigned uy = (unsigned) y;


	/*problems*/
	/*a*/
	(x<y) == (-x>-y);

	/*This is not always true, because -T_MIN == T_MIN. Thus if x == T_MIN
	and y == 5, the expression would return 0 because it gives
	(T_MIN < 5) == (T_MIN > -5)
	and T_MIN cannot be greater than any signed integer. */

	/*b*/
	((x+y)<<4) + y-x == 17*y+15*x;

	/*this can be simplified to: */
	((x+y)<<4) == 16*x+16*y;
	/*This is a true statement, because performing a left shift is
	equivalent to multiplying by 2; 4 left shifts multiplies by 16. */	

	/*c*/
	~x+~y+1 == ~(x+y);
	
	/*This doesnt work because the boolean NOT expression does not
	commute over parenthesis. For example if x = 1 and y = F,
	~1 + ~F + 1 == E + 0 + 1 == 0F.

	~(1+F) == ~00011111 == 111000000 == E0.

	*/

	/*d*/
	(ux-uy) == -(unsigned)(y-x);
	/*This doesn't work because y-x could be a negative number, which
	would screw up the binary when converting to unsigned.

	consider
	x = -4
	y = -8

	so,
	ux == 0100
	uy == 1000
	x  == 1100
	y  == 1000


	y-x == -4 == 1100
	1100 cast to unsigned becomes 12.
	thus the right side would be -12.

	meanwhile the left side would be ux-uy, or -4+8 == 4.
	*/ 

	/*e*/
	((x >> 2) << 2) <= x;

	/*This is true because we are essentially dropping the last 2 bits of 
	x and replacing them with 0s. These are the +1 and +2 places for x, 
	so changing both to 0 will reduce the fuction by between 0 and 3, 
	depending on whehter they were 00, 01, 10, or 11. The only way the final
	result could be lower than the original is if we could somehow drop
	the leading negative bit, but this is impossible because we have a 32
	bit word size and we only shift 2 bits.  */


}
