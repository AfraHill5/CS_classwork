/* Write a c expression that will yield a word consisting of the least
   significant byte of x and the remaining bytes of y. For operands  	
   x = 0x89ABCDEF and y=0x76543210, this would give 0x765432EF. */

#include <stdio.h>
unsigned int foo(int x, int y)
{
	unsigned int xNew = (unsigned) (x % 256); /* 256 = 2 ^ 8 bits */
	unsigned int yNew = (unsigned) (y - (y % (256))); 
	return (xNew + yNew);
}




