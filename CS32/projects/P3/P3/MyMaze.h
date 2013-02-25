#ifndef _MYMAZE_H_
#define _MYMAZE_H_

#include "Maze.h"

class MyMaze: public Maze
{
  public:
	  //housekeeping
	MyMaze(GraphManager* gm) : Maze(gm) {} //constructor
	~MyMaze() {}; //destructor

	//functions
	bool LoadMaze(const std::string &sMazeFile); //called whenever a new maze is loaded; sets the distances
	bool GetNextCoordinate(int curX, int curY, int& newX, int& newY); //determines the next target space for monsters
	

private:
	void setDistances(int maze[MAZE_HEIGHT][MAZE_WIDTH], int sX, int sY); //sets the distances from the maze file
	int distances[MAZE_HEIGHT][MAZE_WIDTH]; //holds the distances from the origin for the monsters
};

#endif //  _MYMAZE_H_
