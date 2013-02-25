unsigned int unsigned_high_prod(unsigned x, unsigned y)
{
	unsigned getHighVals = 0xffff0000;

	/*use this value to & with x and y to split the "high"
	bits so they can be calculated seperately */

	unsigned highX = (x & getHighVals);
	unsigned highY = (y & getHighVals);

	/*since the bitwise functions are identical for signed and unsigned
	multiplication, we can just call the signed_high_prod function with 
	unsigned integers via casting, and then change the answer back to
	unsigned interpretation. */

	int answer = signed_high_product(((int)highX), ((int)highY));
	return ( (unsigned) answer);
}
