//Zach North
//603 885 768
//Homework 2, Problem 1 -- Mazestack function

#include <iostream>
#include <iomanip>
#include <stack>
using namespace std;

class Coord
{
  public:
	Coord (int rr, int cc) : m_r(rr), m_c(cc) {};
	int r() const {return m_r;}
	int c() const {return m_c;}
	
  private:
	  int m_r;
	  int m_c;
};

void determineDistances(const char maze[][10], int sr, int sc, int dist[][10])
{
        // For each reachable position in maze, set the corresponding
		// position of dist to the shortest distance from (sr,sc) to that
		// position.  For each wall or unreachable position in the maze,
		// set the corresponding position in dist to 99

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			dist[i][j] = 99; //sets every element of the distance array to 99

	dist[sr][sc] = 0; //sets the starting position to 0
	stack<Coord> distStack; //initializes a new stack to get the distances

	Coord originCoord(sr, sc); //initializes the first coordinate

	distStack.push(originCoord); //pushes the starting coordinates onto the stack
	while (!distStack.empty())
	{
		Coord currentCoord = distStack.top(); //sets the current coordinate to the top coordinate on the stack
		distStack.pop();

		int m; //integer to track the minimum value
		int r = currentCoord.r(); int c = currentCoord.c(); //integers to track the current values of Coord
		int rightValue = dist[r+1][c];
		int leftValue = dist[r][c+1];
		int upValue = dist [r-1][c];
		int downValue = dist[r][c-1]; //integers to track the values surrounding the current Coord

		if (rightValue > downValue && rightValue > upValue && rightValue > leftValue) //determines which of the 4 directions have the smallest value
			m = rightValue;
		if (downValue > upValue && downValue > leftValue)
			m = downValue;
		if (upValue > leftValue)
			m = upValue;
		else 
			m = leftValue;
		
		if (dist[r][c] > m+1) //if the current value is 2 or greater than the minimum of the 4 adjacent distances
			dist[r][c] = m+1; //sets it to be only 1 higher

		int v = dist[r][c];
		if (maze[r-1][c] == '.') //if you can move up
		{
			if (dist[r-1][c] > v+1) //if the distance value is greater than the current value +1
			{
				dist[r-1][c] = v+1; //set it to the current value +1
				Coord temp(r-1,c);
				distStack.push(temp); //pushes the next coord onto the stack
			}
		}

		if (maze[r+1][c] == '.') //if you can move down
		{
			if (dist[r+1][c] > v+1) //if the distacne value is greater than the current value +1
			{
				dist[r+1][c] = v+1;
				Coord temp(r+1,c);
				distStack.push(temp);
			}
		}

		if (maze[r][c-1] == '.') //if you can move left
		{
			if (dist[r][c-1] > v+1) //if the distance value is greater than the current value +1
			{
				dist[r][c-1] = v+1;
				Coord temp(r,c-1);
				distStack.push(temp);
			}
		}

		if (maze[r][c+1] == '.') //if you can move right
		{
			if (dist[r][c+1] > v+1) //if the distacne value is greater than the current value +1
			{
				dist[r][c+1] = v+1;
				Coord temp(r,c+1);
				distStack.push(temp);
			}
		}
	}
}


//TEST FUNCTION DO NOT MODIFY
int main()  
{
	char myMaze[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X'},
		{ 'X','.','.','.','.','.','X','.','.','X'},
		{ 'X','X','.','X','X','.','.','.','.','X'},
		{ 'X','.','.','X','.','.','.','X','.','X'},
		{ 'X','.','.','.','X','X','.','X','X','X'},
		{ 'X','X','X','.','.','.','.','X','.','X'},
		{ 'X','X','.','.','.','X','.','X','.','X'},
		{ 'X','X','.','X','.','X','.','X','X','X'},
		{ 'X','X','.','.','.','X','.','.','.','X'},
		{ 'X','X','X','X','X','X','X','X','X','X'}
	};

	int distances[10][10];
	determineDistances(myMaze, 6, 3, distances);
	for (int r = 0; r < 10; r++)
	{
		for (int c = 0; c < 10; c++)
			cout << ' ' << setw(2) << distances[r][c];
		cout << endl;
	}
              // Output should be
              //  99 99 99 99 99 99 99 99 99 99
              //  99  7  6  7  8  9 99  9 10 99
              //  99 99  5 99 99  8  7  8  9 99
              //  99  5  4 99  8  7  6 99 10 99
              //  99  4  3  2 99 99  5 99 99 99
              //  99 99 99  1  2  3  4 99 99 99
              //  99 99  1  0  1 99  5 99 99 99
              //  99 99  2 99  2 99  6 99 99 99
              //  99 99  3  4  3 99  7  8  9 99
              //  99 99 99 99 99 99 99 99 99 99
}