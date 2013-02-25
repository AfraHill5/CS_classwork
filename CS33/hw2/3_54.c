3.54

int decode2(int x, int y, int z)
{
	int t = y-z;
	int s = (t<<31) >> 31; 
	t *= x;

	return (t ^ s);
}
