/* 
 * CS:APP Data Lab 
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#include "btest.h"
#include <limits.h>

/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info.
 */
team_struct team =
{
   /* Your login ID */
    "north", 
   /* Student name: Replace with the full name */
   "Zach North",
};

#if 0
/*
 * STEP 2: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
#endif

/*
 * STEP 3: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest test harness to check that your solutions produce 
 *      the correct answers. Watch out for corner cases around Tmin and Tmax.
 */
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {

  return ((~x) & (~y));

}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 2
 */
int bitXor(int x, int y) {

  return ( (~(x & y)) & ~((~x) & (~y)));

}
/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
	return (!(!(~(x ^ ~y))));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	n = n << 3; /*multiplies n by 8 bc 8 bits in a byte */	
  	x = x >> n; /*moves the wanted byte into the last 8 bits */
	return (x & 0xff);
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {

	x = x << 31; /*shifts the LSB to MSB*/
	x = x >> 31; /*exploits the arithmatic shift*/
  	return x;

}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 1 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3 
 */
int logicalShift(int x, int n) {

	int temp = 1;
	temp = temp << 31; /*temp = 1000...*/
	temp = temp >> n; /*fills 1s in n spaces from the MSB */
	temp = temp << 1;/*need to keep the first digit. */

	x = x >> n; /*shifts x over arithmatically*/
	return (x & ~temp); /*0s out the first n values*/

}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {

	/*going to add bits by splitting the 32 bits in half repeatedly
	using masks and adding until all addition becomes "vertical"*/

	/*first need to declare our masks*/
	unsigned mask1 = 0x55;
	unsigned mask2 = 0x33;
	unsigned mask3 = 0x0F;


	mask1 = (mask1 << 8) + 0x55;
	mask1 = (mask1 << 8) + 0x55;
	mask1 = (mask1 << 8) + 0x55; /*shift it 3x so it is now 0x55555555*/
	/*mask1 = 010101...*/

	mask2 = (mask2 << 8) + 0x33;
        mask2 = (mask2 << 8) + 0x33;
        mask2 = (mask2 << 8) + 0x33;
	/*mask2 = 00110011...*/

	mask3 = (mask3 << 8) + 0x0F;
        mask3 = (mask3 << 8) + 0x0F;
        mask3 = (mask3 << 8) + 0x0F;
	/*mask3 = 00001111...*/

	x = x + (~((x>>1) & mask1) + 1); /*first split*/
	x = (x & mask2) + ((x >>2) & mask2); /*split 2*/
	x = (x & mask3) + ((x >>4) & mask3); /*split 3*/
	/*now we can just add the bits until they are "stacked" entirely*/

	x = x + (x>>8);
	x = x + (x>>16);

	/*the answer has a max size of 32, so & it with the last 6 bits*/
	return (x & 0x3F /*00...111111*/);
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	int signX = (x >> 31); /*either 0 or 1 depending on sign*/
	int flipSignX = (((~x) + 1) >> 31); /*this should be 1 or 0 */

	/*The only time signX and flipSignX are both 0 is if x was originally
	0. This is because adding 1 to ~0 == 0 */

	return ((~(signX | flipSignX)) & 1);
}


/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 4 
 */
int leastBitPos(int x) {

	return (x & (~x + 1));

}
/* 
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) {

	return ((1<<31)>>31);

}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {

	x = x >> 31; /*only keep the sign bit*/

  	return (~x & 1);

}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {

	/*exploits -z == ~z + 1 */

	int xMSB = (x>>31) & 1;
	int yMSB = (y>>31) & 1; /*x most sig bit, y most sig bit */


	return (
	( /*first calc is if the signs are the same*/
	  (!(xMSB ^ yMSB)) & /*x and y have the same sign*/ 
	  ((y + (~x + 1) /*y-x*/ )>>31 & 1) /*y-x is a negative number*/
	) 
	| /*next, if the signs are different and y is negative, x>y */
	(
	  (xMSB ^ yMSB) & /*x and y have different signs*/
	  (yMSB & 1) /*y is negative*/
	));
	  
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	/*first have to compute the bias so rounds towards 0 */
	/*we only add the bias if x < 0, so we can use its MSB as the start
	if it is 0 we do nothing, if it is 1 we will add something */

	int xMSB = ((x>>31) & 1);
	int bias = xMSB;
	bias = bias << n;
	bias += ((xMSB<<31) >>31); /*1<<31>>31 == -1, or still 0 if xMSB = 0*/

	return ((x + bias) >> n);
	

}
/* 
 * abs - absolute value of x (except returns TMin for TMin)
 *   Example: abs(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int abs(int x) {

	int sign = ((x >> 31) & 1) << 31 >> 31; /*1 if negative, 0 if x>=0 */
				/*0xffffffff if negative, 0x0 if x>=0 */
	
	int flip = (((~x) + 1) & sign);  /*if negative, flip = -x;
					   if positive, flip  == 0  */
	return x + flip + flip;
	/*either flips x if it is negative, or does nothing if it is positive */
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {

	int xMSB = (x >> 31) & 1; /*tracks the most significant bit of x */
	int yMSB = (y >> 31) & 1; /*y's MSB*/
	int totalMSB = ((x + y) >> 31) & 1; /*the MSB of the total */

	return ((xMSB ^ yMSB) | !((xMSB & yMSB) ^ totalMSB));
	/*either the xMSB and yMSB are different, or if they are the same they
	must be the same as the totalMSB (otherwise there was overflow */
}
