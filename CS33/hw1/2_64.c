/*Return 1 when any odd bit of x = 1; 0 otherwise. Assume w=32. */
int any_odd_one(unsigned x)
{
	unsigned int a = 0x55555555; /*0101010...01*/
	/*assuming odd is counted least significant to most significant.
	if counting most to least, use 0xAAAAAAAA*/

	return !((a & x) == 0);
	/*only positive if there is a 1 in an odd position*/

}

