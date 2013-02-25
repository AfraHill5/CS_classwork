//Added by me 1/7

#include <iostream>
#include "History.h"
using namespace std;

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	for (int r = 0; r < MAXROWS; r++) //sets the history grid to be all zeroes
		for (int c = 0; c < MAXCOLS; c++)
			m_arenaHistory[r][c] = 0;
}

bool History::record(int r, int c)
{
	if (r > m_rows || c > m_cols) //checks if the inputted position is outside of the grid
		return false;

	m_arenaHistory[r-1][c-1]++; //increments the history at that particular space by one
	return true;
}

void History::display() const
{
	//clears the screen and displays the history grid instead
	clearScreen();
	//must replace numbers in the array with '.'s if history is 0, the number if history is 1-8, and 9 if the history is 9+.
	for (int r = 0; r < m_rows; r++) //displays the grid
    {
        for (int c = 0; c < m_cols; c++)
		{
			int current = m_arenaHistory[r][c];
			if (current == 0) //displays a . if the history value is 0
				cout << '.';
			else if (current > 0 && current < 9)
				cout << current;
			else //displays a 9 if the history value is greater than 9
				cout << '9';
		}
        cout << endl;
    }
    cout << endl;
}