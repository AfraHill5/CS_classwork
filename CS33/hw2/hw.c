2.87

Format A:			Format B:
1 sign bit			1 sign bit
5 exp bits (bias = 15)		4 exp bits (bias = 7)
3 frac bits			4 frac bits

rounding is towards +infinity

Bits			Value			Bits				Value
1 01111 001		-9/8			1 0111 0010			-9/8
0 10110 011		176				0 1110 0110			176
1 00111 010		-5/1024			1 0000 0000 		-0
0 00000 111 	15/131072		0 0000 0000			0
1 11100 000		-8192			1 1111 0000 		-infinity		
0 10111 100		384				0 1111 0000 		infinity

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

3.54

int decode2(int x, int y, int z)
{
	int t = y-z;
	int s = (t<<31) >> 31; 
	t *= x;

	return (t ^ s);
}

3.56
int loop(int x, int n)
{
	int result = __;
	int mask;
	for (mask = __; mask = __; mask = __)
	{
		result ^= __;
	}
	return result;
}

A. 
x is in register %esi
n is in register %ebx
result is in register %edi
mask is in register %edx

B.
result's initial value is -1
mask's initial value is 1

C.
It is tested for whether or not it is 0.

D. 
Mask gets shifted by (n << 16)

E.
It gets ^d with the result of (x & mask)

F.
int loop(int x, int n)
{
	int result = -1;
	int mask;
	for (mask = 1; mask != 0; mask = mask << n)
	{
		result ^= (mask & x);
	}
	return result;
}

3.59
int switch_prob(int x, int n)
{
	int result = x;
	
	switch(n)
	{
		/*values less than 50 will be negative, so unsigned comparison will return n > 55 */
		case 50:
		case 52:
			x = x << 2;
			break;
		
		case 53:
			x = x >> 2;
			break;
		
		case 54:
			x *= 3; /*lea exploitation*/
			/*no break*/
		
		case 55:
			x *= x;
		
		case 51: /*default*/
		default: /*n > 55*/
			x += 10;
	}
	return result;
}

3.60
int A[R][S][T];

int store_ele(int i, int j, int k, int *dest)
{
	*dest = A[i][j][k];
	return sizeof(A);
}

A.
Equation 3.1:
For an array declared as

Type D[R][C], 

array element D[i][j] is at address

&D[i][j] = xd + L(C*i + j)

where L is the size of the data type in bytes.

A. It follows that for an array declared as
Type D[R][S][T], 

array element D[i][j][k] is at address

&D[i][j][k] = xd + L(R(S*i + j) + k)

B.
i is at %ebp+8, j is at +12, k is at +16, dest is at +20

movl 	12(%ebp), %edx 				#moves j to %edx
leal	(%edx, %edx, 4), %eax		#multiplies %edx times 5, stores in %eax
leal 	(%edx, %eax, 2), %eax		#multiplies %eax times 2 and adds %edx (stores in %eax)
imull	$99, 8(%ebp), %edx 			#multiplies 99*x and stores it in %edx
addl	%edx, %eax					#adds %edx to %eax
addl	16(%ebp), %eax 				#adds k to %eax
movl 	A(,%eax, 4), %edx			#multiplies %eax * 4 and adds A
movl 	20(%ebp), %eax				#moves dest into %eax
movl	%edx, (%eax)				#moves %edx to the address pointed by %eax (dest)
movl 	$1980, %eax					#moves 1980 into %eax

eax = dest
edx = A + 4(11j + 99x + k)

Registers look like this ^ before the last 2 lines are executed.
xd + L(R(S*i + j) + k) = A + 4(11j + 99x + k)
xd = A
L = 4

(R(S*i + j) + k) = (99x + 11j + k) = (11(9x + j) + k)
R = 11
S = 9


Since it returns 1980 as sizeof, we know the size of the array is 1980 bytes
which is L(R*S*T)
1980 = 4(11*9*T) = 396T
T = 5

RESULTS: 
R = 11
S = 9
T = 5


3.61
Get from lnxsrv

3.64
A.
The three values are the two values stored in s1 (a and p) and a pointer to memory for 
the struct result. Values can be stored in result by incrementing the pointer 4 bytes at a time

B.
4 bytes for s1.a
4 bytes for s1.p
4 bytes for s2.sum
4 bytes for s2.diff
4 bytes for the value to be returned (s2.sum * s2.diff)

C.
Generally the compiler stores each element of the struct in a seperate register. It
pushes the results into memory based on the composition of the struct it is returning,.

D.
A struct being returned from a function is basically just a "stack" of values in the order
they are declared. For example, a struct containing an int and a double would ust be represented
in memory by an int followed immediately by a double. You could operate on the element of the
struct you wanted by incrementing the stack pointer "down the list" until you reached your element.