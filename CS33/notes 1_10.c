//Lectures: Higher level concepts
//Discussions: Applied concepts
//Labs: Central to the course; pracical programming experience

//Office Hours are after class in Boelter
//HW is due via CourseWeb by Midnight on Fridays, graded on completeness

//Exams major emphasis is on material presented in lecture, although book
//content will be present

//Seas admin linux machine: lnxsrv02.seas.ucla.edu
//remote acces only, use ssh to login with Seas account

//Course theme: abstraction is good, but don't forget reality.
//Abstractions have limits, especially in the presence of bugs. Need to
//understand underlying implementations

//C is base language of the course. It allows low level access to memory,
//pointers; it maps efficiently to machine instructions and is efficient
//at run time.

//C is not "write once, run everywhere"; there are different compilers for
//different architectures. A good C programmer can minimize the number
//of changes needed to port to a new platform

#include <stdio.h>
int main()
{
	printf("hello, world\n");
}

//ints are not integers, floats are not real numbers.
//limited by memory allocation for numbers.
//is x^2 >= 0?
//floats: yes
//ints: -40000 * 40000 = 1600000000
//		-50000 * 50000 = ?

//is (x+y) +z = x + (y+z)?
//ints: yes
//floats: not always

//you have to know assembly at some level. you will probably never 
//program in assembly but you need to know it.

//memory allocation, reference, etc will be covered. C does not provide any 
//memory protection or exceptions for invalid pointer values.

//you have to know how code works on a basic level to be best able to 
//optimize your algorithms, data, procedures, and loops

