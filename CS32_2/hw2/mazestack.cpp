#include <stack>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};


bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	//returns true if there is a path from (sr, sc) to (er,ec) thru
	//the maze; otherwise false

	//maze is 10x10, x == wall, . == walkway.
	//coords range from (0,0) to (9,9)

	stack<Coord> coordStack;
	Coord c(sr, sc);
	coordStack.push(c);
	maze[sr][sc] = '@'; //this indicates we have checked this spot
	//need to check the surrounding paths 
	while (coordStack.size() != 0)
	{
		Coord curr = coordStack.top();
		coordStack.pop(); //gets the first value in the stack
		if (curr.c() == ec && curr.r() == er) //at the end
			return true;

		int r = curr.r();
		int c = curr.c();
		//check all 4 directions
		if (maze[r-1][c] == '.') //N
		{
			coordStack.push(Coord(r-1, c)); //if we can move N, pushes onto stack
			maze[r-1][c] = '@';
		}

		if (maze[r][c+1] == '.') //e
		{
			coordStack.push(Coord(r, c+1));
			maze[r][c+1] = '@';
		}

		if (maze[r+1][c] == '.') //S
		{
			coordStack.push(Coord(r+1, c));
			maze[r+1][c] = '@';
		}
		if (maze[r][c-1] == '.') //W
		{
			coordStack.push(Coord(r, c-1));
			maze[r][c-1] = '@';
		}
		
	}
	return false;
}


#include <iostream>
int main()
	{
	    char maze[10][10] = {
	        { 'X','X','X','X','X','X','X','X','X','X'},
	        { 'X','.','.','.','.','X','.','.','.','X'},
	        { 'X','.','X','X','.','X','X','.','.','X'},
	        { 'X','.','X','.','.','.','X','.','.','X'},
	        { 'X','X','X','X','X','.','X','.','.','X'},
	        { 'X','.','X','.','.','.','X','.','.','X'},
	        { 'X','.','.','.','X','.','X','.','.','X'},
	        { 'X','X','X','X','X','.','X','X','X','X'},
	        { 'X','.','.','.','.','.','.','.','.','X'},
	        { 'X','X','X','X','X','X','X','X','X','X'}
	    };
	
	    if (pathExists(maze,1,1,8,8))
	        cout << "Solvable!" << endl;
	    else
	        cout << "Out of luck!" << endl;
	}
	