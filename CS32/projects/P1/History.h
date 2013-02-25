//Added by me 1/7
#ifndef HISTORY_H_INCLUDE
#define HISTORY_H_INCLUDE

#include "globals.h"

class History
{
  public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
  private:
	int m_rows;
	int m_cols;
	int m_arenaHistory[MAXROWS][MAXCOLS];
};

#endif