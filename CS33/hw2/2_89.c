2.89

float fpwr2(int x)
{
	/*result exponent and fraction */
	unsigned exp, frac;
	unsigned u;

	if (x < -126)
	{
		/*too small. return 0.0*/
		exp = 0;
		frac = 0;
	}
	else if (x < -125)
	{
		/*denormalized result*/
		exp = 0;
		frac = 1;
	}
	else if (x < 127 )
	{
		/*normalized result*/
		exp = x;
		frac = 1;
	}
	else
	{
		/*too big, return +oo*/
		exp = 0xff;
		frac = 0;
	}

	/*pack exp and frac into 32 bits */
	u = exp << | frac;
	/*return as float */
	return u2f(u);
}


