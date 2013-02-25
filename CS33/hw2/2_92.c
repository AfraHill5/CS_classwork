2.92

/*Compute |f|. If f is NaN, then return f. */
#include "stdio.h"
typedef float float_bits;

float_bits float_absval(float_bits f)
{
	if (f != f) /*NaN*/
		return f;
	int u = (unsigned) f;
	u &= 0x7fffffff;
	return ((float_bits)u);
}


