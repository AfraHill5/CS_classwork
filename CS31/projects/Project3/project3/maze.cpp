//Zach North
//603-885-768
//Project 3


#include "grid.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

bool isPathWellFormed (string path)
{
	string instructions; // this will be the converted lowercase version of the inputted string
	int digitCounter = 0; // this will be used to make sure no more than 2 digits are in a row
	for (size_t k = 0; k != path.size(); k++)
	{
		instructions += tolower(path.at(k)); //converts the inputted string to lowercase
	}
	for (size_t j = 0; j != instructions.size(); j++)
	{
		if (!isalpha(instructions.at(0)))
			return 0;  // if the first character is not a letter, display error message.
		if (isdigit(instructions.at(j)))
			digitCounter += 1; //if the character being evaluated is a digit, this adds one to the counter
		else if (isalpha(instructions.at(j)))
		{
			digitCounter = 0; //resets the digit counter whenever a letter is in the string
			if (instructions.at(j) != 'n' && instructions.at(j) != 'e' && instructions.at(j) != 'w' && instructions.at(j) != 's')
				return 0;  //inputted letters must be in a cardinal direction i.e. one of the 4 letters, else error
			if (!isdigit(instructions.at(j + 1)))
				return 0; //can't have direction without a digit following
		}
		else
			return 0; //the character is not a letter or a digit, so the string is invalid

		if (digitCounter > 2)
			return 0; // if more than 2 digits are ever in a row, this returns an error.
		 
	}
	return 1; // if the program makes it to here, the input was correct
}

int followSegment (int r, int c, char dir, int maxSteps)
{
	int totalSteps = 0; //counter for the number of steps taken

	if (r <= 0 || r > getRows()) //checks to see that rows is in the correct domain
		return -1;
	if (c <= 0 || c > getCols()) //checks to see that cols is in the correct domain
		return -1;
	if (maxSteps < 0) //maxSteps has to be positive
		return -1;
	if (isWall(r, c) == 1) //checks first to see if initial position is located "inside" a wall.
		return -1;
	if (dir != 'n' && dir != 'N' && dir != 'w' && dir != 'W' && dir != 'e' && dir != 'E' && dir != 's' && dir != 'S') // checks directions for validity
		return -1;
	if (dir == 'n' || dir == 'N') // for going north
		for (int k = 0; k < maxSteps; k++) 
		{
			if (r == 1) // breaks if hits the top of the grid
				break;
			if (isWall((r - 1), c) == 1) // breaks if next step would be a wall
				break;
			r -= 1;
			totalSteps += 1;
		}
	if (dir == 'w' || dir == 'W') //west
		for (int k = 0; k < maxSteps; k++)
		{
			if (c == 1) //breaks if hits the left side of the grid
				break;
			if (isWall(r, (c - 1)) == 1) //breaks if next step would be a wall
				break;
			c -= 1; 
			totalSteps += 1;
		}
	if (dir == 'e' || dir == 'E') //east
		for (int k = 0; k < maxSteps; k++)
		{
			if (c == (getCols())) //breaks if hits the right side of the grid
				break;
			if (isWall(r, (c + 1)) == 1) //breaks if next step would be a wall
				break;
			c += 1;
			totalSteps += 1;
		}
	if (dir == 's' || dir == 'S') //south
		for (int k = 0; k < maxSteps; k++)
		{
			if (r == (getRows())) //breaks if hits the bottom side of the grid
				break;
			if (isWall((r + 1), c) == 1) //breaks if next step would be a wall
				break;
			r += 1;
			totalSteps += 1;
		}
	return totalSteps; //once the function either hits a wall or executes the max number of steps,
	                   //it returns the number of steps taken
}

int convertCharToInt (char input) //used to convert parsed integer values from char to int
{
	return (input - '0');
}

int followPath (int sr, int sc, int er, int ec, string path, int& nsteps)
{
	int columnPosition = sc;
	int rowPosition = sr; //used in loops to check interval position
	bool wallCheck = 0; //activated if the robot hits a wall

	if (!isPathWellFormed(path)) // checks that path is valid
		return 3; //syntax error

	for (size_t k = 0; k != path.size(); k++) //This loop assigns char variables to the first 3 digits of path. It checks the first one for the direction and then
		                                      //determines how many spaces to move based on then following 2 variables -- if only the next char is a number, it will
											  //use that digit as the number of steps to take; however, if both following chars are numbers, it will use the first
											  //one times 10, plus the second one times 1 (standard decimal notation.)
	{
		char currentChar = path.at(k); //assigns a char variable to the current character being parsed
		char nextChar = ' ';
		int nextCharInt = 0;
		char farChar = ' ';
		int farCharInt = 0;

		if (isalpha(path.at(k))) // only runs this if the current character is a direction
			if (k < (path.size() - 1)) 
				nextChar = path.at(k + 1); //assigns a char variable to the next character
			else
				; //if it reaches the end of the string, prevents undefined behavior
			if (k < (path.size() - 2))
				farChar = path.at(k + 2); // assigns a char variable to the next next character
			else
				; //prevents undefined behavior



		switch (currentChar)
		{
			case 'n':
			case 'N':
				{
					if (isdigit(farChar)) //if there are 2 digits trailing the direction
					{
						int tempSteps = 0;
						tempSteps += (convertCharToInt(nextChar) * 10); // add the first digit times 10
						tempSteps += (convertCharToInt(farChar)); // add the second digit times 1
						nsteps += followSegment(rowPosition, columnPosition, 'n', tempSteps); //adds the number of steps taken to the counter
						if (tempSteps != followSegment(rowPosition, columnPosition, 'n', tempSteps))
							wallCheck = 1;
						rowPosition -= followSegment(rowPosition, columnPosition, 'n', tempSteps); //adjusts the position to the maximum allowed by the followSegment function
						break;
					}
					else //1 digit trailing the direction
					{
						int tempSteps = 0;
						tempSteps += (convertCharToInt(nextChar)); // add the first digit times 1
						nsteps += followSegment(rowPosition, columnPosition, 'n', tempSteps); //adds the number of steps taken to the counter
						if (tempSteps != followSegment(rowPosition, columnPosition, 'n', tempSteps))
							wallCheck = 1;
						rowPosition -= followSegment(rowPosition, columnPosition, 'n', tempSteps); //adjusts the position to the maximum allowed by the followSegment function
						break;
					}
				}
			case 'w':
			case 'W':
				{
					if (isdigit(farChar)) //if there are 2 digits trailing the direction
					{
						int tempSteps = 0;
						tempSteps += (convertCharToInt(nextChar) * 10); // add the first digit times 10
						tempSteps += (convertCharToInt(farChar)); // add the second digit times 1
						nsteps += followSegment(rowPosition, columnPosition, 'w', tempSteps); //adds the number of steps taken to the counter
						if (tempSteps != followSegment(rowPosition, columnPosition, 'w', tempSteps))
							wallCheck = 1;
						columnPosition -= followSegment(rowPosition, columnPosition, 'w', tempSteps); //adjusts the position to the maximum allowed by the followSegment function
						break;
					}
					else //1 digit trailing the direction
					{
						int tempSteps = 0;
						tempSteps += (convertCharToInt(nextChar)); // add the first digit times 1
						nsteps += followSegment(rowPosition, columnPosition, 'w', tempSteps); //adds the number of steps taken to the counter
						if (tempSteps != followSegment(rowPosition, columnPosition, 'w', tempSteps))
							wallCheck = 1;
						columnPosition -= followSegment(rowPosition, columnPosition, 'w', tempSteps); //adjusts the position to the maximum allowed by the followSegment function
						break;
					}
				}
			
			case 'e':
			case 'E':
				{
					if (isdigit(farChar)) //if there are 2 digits trailing the direction
					{
						int tempSteps = 0;
						tempSteps += (convertCharToInt(nextChar) * 10); // add the first digit times 10
						tempSteps += (convertCharToInt(farChar)); // add the second digit times 1
						nsteps += followSegment(rowPosition, columnPosition, 'e', tempSteps); //adds the number of steps taken to the counter
						if (tempSteps != followSegment(rowPosition, columnPosition, 'e', tempSteps))
							wallCheck = 1;
						columnPosition += followSegment(rowPosition, columnPosition, 'e', tempSteps); //adjusts the position to the maximum allowed by the followSegment function
						break;
					}
					else //1 digit trailing the direction
					{
						int tempSteps = 0;
						tempSteps += (convertCharToInt(nextChar)); // add the first digit times 1
						nsteps += followSegment(rowPosition, columnPosition, 'e', tempSteps); //adds the number of steps taken to the counter
						if (tempSteps != followSegment(rowPosition, columnPosition, 'e', tempSteps))
							wallCheck = 1;
						columnPosition += followSegment(rowPosition, columnPosition, 'e', tempSteps); //adjusts the position to the maximum allowed by the followSegment function
						break;
					}
				}

			case 's':
			case 'S':
				{
					if (isdigit(farChar)) //if there are 2 digits trailing the direction
					{
						int tempSteps = 0;
						tempSteps += ((convertCharToInt(nextChar)) * 10); // add the first digit times 10
						tempSteps += (convertCharToInt(farChar)); // add the second digit times 1
						nsteps += followSegment(rowPosition, columnPosition, 's', tempSteps); //adds the number of steps taken to the counter
						if (tempSteps != followSegment(rowPosition, columnPosition, 's', tempSteps))
							wallCheck = 1;
						rowPosition += followSegment(rowPosition, columnPosition, 's', tempSteps); //adjusts the position to the maximum allowed by the followSegment function
						break;
					}
					else //1 digit trailing the direction
					{
						int tempSteps = 0;
						tempSteps += (convertCharToInt(nextChar)); // add the first digit times 1
						nsteps += followSegment(rowPosition, columnPosition, 's', tempSteps); //adds the number of steps taken to the counter
						if (tempSteps != followSegment(rowPosition, columnPosition, 's', tempSteps))
							wallCheck = 1;
						rowPosition += followSegment(rowPosition, columnPosition, 's', tempSteps); //adjusts the position to the maximum allowed by the followSegment function
						break;
					}
				}

				default: //if the character is a number, go on to the next one
					;
		}
			

			
	}
	
	//cout << "Position: (" << rowPosition << ',' << columnPosition << ')' << endl; //DEBUG
	//cout << "Steps taken: "<< nsteps << endl; //DEBUG

	if (wallCheck == 1)
		return 2; //hit the wall at some point
	else if (rowPosition == er && columnPosition == ec)
		return 0; //if the final position of the robot is the desired ending position, returns a 0
	else
		return 1; //else returns a 1
}




int main()
	{
		//adjust these to change starting position
		int startRow = 1;
		int startCol = 1;
		int endRow = 7;
		int endCol = 5;
		int wallSizeRows = 12;
		int wallSizeCols = 12;

	    setSize(wallSizeRows,wallSizeCols);      // makes a grid
	    setWall(1,4);      // sets a wall
	    setWall(2,2);      // sets a wall
		setWall(3,7);
		setWall(4,4);
		setWall(5,4);
		setWall(6,4);
	    if (!isWall(3,2))  // if there's no wall at (3,2)  [there isn't]
	        setWall(3,2);  //    put a wall at (3,2)
	    draw(startRow,startCol, endRow,endCol);    // draw the grid, showing an S at (3,1)
	                                               //    start position, and an E at (3,4)

		//tests
		string path;
		cout << "Enter path: ";
		getline(cin, path);
		


		cout << "Syntax test: " << isPathWellFormed (path) << endl; //expresses whether the input is valid syntax
		
		int nsteps = 0;

		cout << "Path test: " << followPath(startRow, startCol, endRow, endCol, path, nsteps) << endl;

		//0 is a success; 1 means you didn't reach the endpoint; 2 means you ran into a wall; 3 means the input was incorrect
	}