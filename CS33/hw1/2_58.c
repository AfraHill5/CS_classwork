
int is_little_endian()
{
	int x = -2; 
	/* all the bits will be 1 except for the last one, which will be 0 */

	unsigned char* startByte = &x;
	/* point to the first byte of the x int */
	if (*(startByte+1)  == '0')
		return 1;
	/* if the computer is little endian the bits will be ordered in 
	   reverse i.e. 10111111... */	

	return 0;
}	  
