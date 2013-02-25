#include "MyMaze.h"
#include <stack>

bool MyMaze::LoadMaze(const std::string &sMazeFile)
{
	Maze::LoadMaze(sMazeFile);
	int tempGrid[MAZE_HEIGHT][MAZE_WIDTH]; //holds the values in the grid in order to compute
	for (int i = 0; i < MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAZE_WIDTH; j++)
		{
			tempGrid[i][j] = GetGridContents(j, i);
		}
	}
	setDistances(tempGrid, GetMonsterStartX(), GetMonsterStartY()); //sets the distance array
	return true;
}

bool MyMaze::GetNextCoordinate(int curX, int curY, int& newX, int&newY)
{
	//sets the next coordinates for the monsters to go to if they are returning home
	int current		=	distances[curY][curX];
	int eastValue	=	distances[curY][curX-1];
	int westValue	=	distances[curY][curX+1];
	int northValue	=	distances[curY-1][curX];
	int southValue	=	distances[curY+1][curX];

	if (current == eastValue+1 && westValue > eastValue && northValue > eastValue && southValue > eastValue) //if eastvalue is the smallest
	{
		newX = curX - 1;
		newY = curY;
		return true;
	}
	
	else if (current == westValue+1 && northValue > westValue && southValue > westValue)//west
	{
		newX = curX + 1;
		newY = curY;
		return true;
	}

	else if (current == northValue+1 && southValue > northValue) //north
	{
		newX = curX;
		newY = curY - 1;
		return true;
	}

	else if (current == southValue+1) //south
	{
		newX = curX;
		newY = curY + 1;
		return true;
	}

	else //home
		return false;
}

void MyMaze::setDistances(int maze[MAZE_HEIGHT][MAZE_WIDTH], int sX, int sY) //((I don't know if this works))
{

	//IMPORTED FROM HW2
        // For each reachable position in maze, set the corresponding
		// position of dist to the shortest distance from (sr,sc) to that
		// position.  For each wall or unreachable position in the maze,
		// set the corresponding position in dist to 99

	for (int i = 0; i < MAZE_HEIGHT; i++)
		for (int j = 0; j < MAZE_WIDTH; j++)
			distances[i][j] = 99; //sets every element of the distance array to 99

	distances[sY][sX] = 0; //sets the starting position to 0
	std::stack<COORD> distStack; //initializes a new stack to get the distances

	COORD originCoord(sX, sY); //initializes the first coordinate

	distStack.push(originCoord); //pushes the starting coordinates onto the stack
	while (!distStack.empty())
	{
		COORD currentCoord = distStack.top(); //sets the current coordinate to the top coordinate on the stack
		distStack.pop();

		int m; //integer to track the minimum value
		int c = currentCoord.x; int r = currentCoord.y; //integers to track the current values of COORD
		int rightValue = 99; int leftValue = 99; int upValue = 99; int downValue = 99;
		if (c > 0)
			leftValue = distances[r][c-1];
		if (c < MAZE_WIDTH - 1)
			rightValue = distances[r][c+1];
		if (r > 0)
			downValue = distances[r+1][c];
		if (r < MAZE_HEIGHT - 1)
			upValue = distances[r-1][c];   //integers to track the values surrounding the current COORD

		if (rightValue < downValue && rightValue < upValue && rightValue < leftValue) //determines which of the 4 directions have the smallest value
			m = rightValue;
		else if (downValue < upValue && downValue < leftValue)
			m = downValue;
		else if (upValue < leftValue)
			m = upValue;
		else 
			m = leftValue;
		
		if (distances[r][c] > m+1) //if the current value is 2 or greater than the minimum of the 4 adjacent distances
			distances[r][c] = m+1; //sets it to be only 1 higher

		int v = distances[r][c];
		if (maze[r-1][c] != WALL) 
			//if you can move up
		{
			if (distances[r-1][c] > v+1) //if the distance value is greater than the current value +1
			{
				distances[r-1][c] = v+1; //set it to the current value +1
				COORD temp(c,r-1);
				distStack.push(temp); //pushes the next coord onto the stack
			}
		}

		if (maze[r+1][c] != WALL) //if you can move down
		{
			if (distances[r+1][c] > v+1) //if the distacne value is greater than the current value +1
			{
				distances[r+1][c] = v+1;
				COORD temp(c,r+1);
				distStack.push(temp);
			}
		}

		if (maze[r][c-1] != WALL) //if you can move left
		{
			if (distances[r][c-1] > v+1) //if the distance value is greater than the current value +1
			{
				distances[r][c-1] = v+1;
				COORD temp(c-1,r);
				distStack.push(temp);
			}
		}

		if (maze[r][c+1] != WALL) //if you can move right
		{
			if (distances[r][c+1] > v+1) //if the distance value is greater than the current value +1
			{
				distances[r][c+1] = v+1;
				COORD temp(c+1,r);
				distStack.push(temp);
			}
		}
	}
}