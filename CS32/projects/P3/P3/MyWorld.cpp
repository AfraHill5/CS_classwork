#include "MyWorld.h"

GameStatus MyWorld::RunLevel()
{
	NachMan* nach = GetNachMan();
	Maze* maze = GetMaze();
	nach->setAlive(true); //sets the nachman to ALIVE
	nach->SetX(maze->GetNachManStartX()); //sets the x coord for NM
	nach->SetY(maze->GetNachManStartY()); //y
	nach->setDirection(NONE); //sets the direction to NONE for initial game start

	for (int i = 0; i < NUM_MONSTERS; i++) //monster initialization
	{
		GetMonster(i)->SetX(maze->GetMonsterStartX());
		GetMonster(i)->SetY(maze->GetMonsterStartY());
	}

	DisplayScreen(true); //starts the game

	while (nach->isAlive() && maze->GetRemainingFood() != 0) //while NM is alive, and pellets remain
	{
		nach->DoSomething(); //move NM
		if (nach->isAlive()) //if nachman didn't kill himself moving
		{
			for (int i = 0; i < NUM_MONSTERS; i++)
			{
				GetMonster(i)->DoSomething(); //move all the monsters
			}
		}

		DisplayScreen(false); //draws the updated screen
	}

	if (maze->GetRemainingFood() == 0) //if all the food was eaten
		return FINISHED_LEVEL; //the player completed the level
	else
		return PLAYER_DIED; //did not complete level
}
