#include "globals.h"
#include "History.h"
#include <iostream>
using namespace std;

//constructor
History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	for (int r = 1; r <= nRows; r++)
	{
		for (int c = 1; c <= nCols; c++)
		{
			m_histGrid[r-1][c-1] = 0; //history should be zero on all squares
		}
	}
}

bool History::record(int r, int c)
{ //returns true if (r,c) is in the arena
	if (r > m_rows || c > m_cols || r < 1 || c < 1)
		return false;
  //if r,c is in the arena, records the player's position to the
  //history and returns true
	if (m_histGrid[r-1][c-1] < 26) //stops recording over 25
		m_histGrid[r-1][c-1]++;
	return true;
}

void History::display() const
{ //displays the arena and players on the screen
	clearScreen();
	
	char charGrid[MAXROWS][MAXCOLS]; 
	for (int r = 1; r <= m_rows; r++)
	{
		for (int c = 1; c <= m_cols; c++)
		{
			if (m_histGrid[r-1][c-1] == 0)
				charGrid[r-1][c-1] = 46; /* 46 == '.'  */
			else //history on that square
				charGrid[r-1][c-1] = 64 /* 'A' is 65 */ + m_histGrid[r-1][c-1];
			//if no history, sets to '.'
			//if some history, sets the grid to the corresponding letter
			cout << charGrid[r-1][c-1]; //outputs the result
		}
		cout << endl;
	}


}

