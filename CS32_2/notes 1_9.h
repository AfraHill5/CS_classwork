//Notes 1/9/2012
//Office hours are Mon 12pm-1pm, Wednesday 9am-10am

//What we're going to learn:
//Advanced C++ topics and OOP
//Data Structures
//Algorithms
//Building Big Programs (500+ lines)

//Midterms:
//1. Wed Feb 1, after class
//2. Wed Feb 22, after class

//Final Exam is the Saturday before finals, 3-6pm

//Goal of project 1 is to allow you to self-evaluate and see if you are
//ready for CS32. It should be very easy and if you can't do it you need
//to take CS31 again to prepare yourself.

//Grading policy: first they compute the average score of the midterm and 
//final exams. The maximum project grade is capped at 30% above this score.

//Must make sure that projects compile on both Visual C++ and cpp (linux)
//Do this at least a couple days before the project is due.

 //Write an algorithm that tests if an array of 100 numbers is a fibonacci
 //sequence.
 
 bool isFib(int arr[])
 {
	int index;
	if (arr[0] != 0 || arr[1] != 1)
		return false;
	for (index = 2; index < 100; index++)
	{
		if (arr[index] != arr[j-1] + arr[j-2])
			return false;
	}
	return true;
}

//Algorithms are sets of instructions/steps that solve a particular problem.
//They can be classified by speed, quality, etc.

//Data structures are data that is operated on by an algorithm to solve
//a problem Sometimes an algorithm can operate just on the data passed
//in to it. Other times, your algorithm will have to create its own
//secondary data structures to solve a problem.

//Example: a data structure for facebook
//I want to keep track of who is friends with who (mutual friends)
//if you used a linear algorithm, storing individual friendships, it
//would take a long time to run through a list of friends to see if 2
//ppl are friends.
//what if instead we assigned each usera  number and kept an alphabetized
//list of each user-number pair? Now we can use binary search to find if
//a person is friends with another.

//Interface functions are simple functions that anyone can use without
//having to know the algorithm behind them. Ex: AreTheyFriends, MakeFriends.
//You don't have to understand the underlying details to understand how to use them.

//Abstract Data Type (ADT) is a coordinated group of data structures, 
//algorithms, and interface functions used to solve a particular problem.

//Generally in an ADT you keep the data structures and algorithms secret.
//There's really no reason for them to be known to the outside -- just the
//interface functions are necessary, or the API.

//C++ classes are the equivalent of ADTs. They provide a public interface,
//private algorithms, and private data structures.

//OOP is a programming model based on the ADT concept just learned. In OOP
//programs are constructed from multiple self-contained classes, each holding
//a set of data and algorithms that are accessed using interface funcs.

//C++ structs
//used to group together multiple pieces of data and store them in one variable.

struct Student
{
	string 	name;
	int		ID;
	float 	GPA;
};

//This defines a new data type like string that we can now use in the program.
//Contain this definition in the header file and then include it in the cpp file.

#include "student.h"

int main()
{
	Student s1;
	Student s2;
	
	s1.name = "Juan";
	s1.ID = 123;
	s1.GPA = 4.0;
	
	s2.name = "Jose";
	s2.ID = 234;
	s2.GPA = 1.0;
}

//The dot operator allows you to access a subelement of a struct/class.

//Classes are structs that can also hold algorithms as well
//as interface functions. Its like a struct with built-in functions.

class Rect
{
	public:
		int getArea()
		{
			int area = width*height;
			return area;
		}
		int width; //normally these would be private
		int height;
};

int main()
{
	Rect r;
	r.width = 10;
	r.height = 20;
	Rect s;
	s.width = 120;
	s.height = 230;
	cout << r.getArea();
	cout << s.getArea();
}

//In C++ lingo r and s would be called "instances" or "objects".
//s is an instance of Rect. r is a Rect object. etc

//Usually when you make classes you define the "behind the scenes" 
//data as private, and interface functions as public.

class Rect()
{
	public:
		int getArea()
		{...}
		void initialize()
		{...}
	private:
		int myComplexAlgorithm();
		
		int height;
		int width;
};
