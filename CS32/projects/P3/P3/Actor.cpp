#include "Actor.h"
#include "MyWorld.h"

//Actor implementations

Actor::Actor()
{
	m_x = 0;
	m_y = 0;
	m_world = NULL;
	setDirection();
	//constructor
}

Actor::~Actor()
{
	//destructor
}

int Actor::GetX()
{
	return m_x;
}

int Actor::GetY()
{
	return m_y;
}

void Actor::SetX(int newXCoord)
{
	m_x = newXCoord;
}

void Actor::SetY(int newYCoord)
{
	m_y = newYCoord;
}

World* Actor::getWorld()
{
	return m_world;
}

void Actor::setWorld(World* w) //my function -- sets the m_world to the input
{
	m_world = w;
}

void Actor::setDirection(Direction d)
{
	m_direction = d;
}

Direction Actor::getDirection()
{
	return m_direction;
}



//NachMan implementations

NachMan::NachMan(World* currentWorld, int X, int Y)
{
	SetX(X);
	SetY(Y);
	setWorld(currentWorld);
	m_alive = true;
	m_lives = 3;
	m_score = 0;
	//doesn't start off facing any direction
} 

NachMan::~NachMan()
{
	//destructor
}

int NachMan::GetNumLivesLeft()
{
	return m_lives;
}

void NachMan::DecrementNumLives()
{
	m_lives--;
}

int NachMan::GetScore()
{
	return m_score;
}

void NachMan::incrementScore(int n)
{
	m_score += n;
}

colors NachMan::GetDisplayColor()
{
	return YELLOW;
}

int NachMan::getMyID()
{
	return ITEM_NACHMAN;
}

void NachMan::DoSomething()
{
	char ch;
	Maze* m = getWorld()->GetMaze();  //pointer to NachMan's current maze
	GridContents next;
	if (getCharIfAny(ch))
	{
		switch(ch)
		{
		case ARROW_LEFT:
			next = m->GetGridContents(GetX()-1, GetY()); //grabs the grid content to the left
			if (next == WALL || next == CAGEDOOR)	//check if there is a wall or monster cage door to the left
				break; //do nothing
			else
				setDirection(WEST);
			break;

		case ARROW_RIGHT:
			next = m->GetGridContents(GetX()+1, GetY()); //grabs the grid content to the right
			if (next == WALL || next == CAGEDOOR)	//check if there is a wall or monster cage door to the right
				break; //do nothing
			else
				setDirection(EAST);
			break;

		case ARROW_UP:
			next = m->GetGridContents(GetX(), GetY()-1); //grabs the grid content to the north
			if (next == WALL || next == CAGEDOOR)	//check if there is a wall or monster cage door to the north
				break; //do nothing
			else
				setDirection(NORTH);
			break;

		case ARROW_DOWN:
			next = m->GetGridContents(GetX(), GetY()+1); //grabs the grid content to the south
			if (next == WALL || next == CAGEDOOR)	//check if there is a wall or monster cage door to the south
				break; //do nothing
			else
				setDirection(SOUTH);
			break;
		}
	}
		//move NachMan in current direction
	int nVulnerableTicks = 0;
	switch(getDirection()) //checks the current direction NachMan is facing
	{
		case WEST:
			next = m->GetGridContents(GetX()-1, GetY());
			switch(next) //checks the next grid spot
			{
			case PELLET:
				//remove pellet from maze
				m->SetGridContents(GetX()-1, GetY(), EMPTY);
				//play PAC_SOUND_EAT
				SoundFX::playNachManSound(PAC_SOUND_SMALL_EAT);
				//increment score
				m_score += 10;
				//move nachman west
				SetX(GetX() - 1);
				break;
	
			case POWERPELLET:
				//remove pellet from maze
				m->SetGridContents(GetX()-1, GetY(), EMPTY);
				//play pacsound
				SoundFX::playNachManSound(PAC_SOUND_BIG_EAT);
				//increment score
				m_score += 100;
				//change states of monster
				if (getWorld()->GetLevel() <= 8)
					nVulnerableTicks = 100 - ((getWorld()->GetLevel()) * 10);
				else
					nVulnerableTicks = 20;
				for (int i = 0; i < NUM_MONSTERS; i++)
				{
					if (getWorld()->GetMonster(i)->getCurrentState() == normal || getWorld()->GetMonster(i)->getCurrentState() == vulnerable)
					{
						getWorld()->GetMonster(i)->setCurrentState(vulnerable); //if the monsters are currently normal/vulnerable, sets them to vulnerable
						getWorld()->GetMonster(i)->setVulnerableCount(nVulnerableTicks);
					}
				}
				//move nachman west
				SetX(GetX() - 1);
				break;
	
			case EMPTY:
				SetX(GetX() - 1);//move nachman to the west
				break;
	
			case WALL:
			case CAGEDOOR: //don't move, hit a wall
				break;
			}
	
			break;
		
		case EAST:
			next = m->GetGridContents(GetX()+1, GetY());
			switch(next) //checks the next grid spot
			{
			case PELLET:
				//remove pellet from maze
				m->SetGridContents(GetX()+1, GetY(), EMPTY);
				//play PAC_SOUND_EAT
				SoundFX::playNachManSound(PAC_SOUND_SMALL_EAT);
				//increment score
				m_score += 10;
				//move nachman east
				SetX(GetX() + 1);
				break;
	
			case POWERPELLET:
				//remove pellet from maze
				m->SetGridContents(GetX()+1, GetY(), EMPTY);
				//play pacsound
				SoundFX::playNachManSound(PAC_SOUND_BIG_EAT);
				//increment score
				m_score += 100;
				//change states of monster
				if (getWorld()->GetLevel() <= 8)
					nVulnerableTicks = 100 - ((getWorld()->GetLevel()) * 10);
				else
					nVulnerableTicks = 20;
				for (int i = 0; i < NUM_MONSTERS; i++)
				{
					if (getWorld()->GetMonster(i)->getCurrentState() == normal || getWorld()->GetMonster(i)->getCurrentState() == vulnerable)
					{
						getWorld()->GetMonster(i)->setCurrentState(vulnerable); //if the monsters are currently normal/vulnerable, sets them to vulnerable
						getWorld()->GetMonster(i)->setVulnerableCount(nVulnerableTicks);
					}
				}
				//move nachman east
				SetX(GetX() + 1);
				break;

			case EMPTY:
				SetX(GetX() + 1);//move nachman to the east
				break;
			case WALL:
			case CAGEDOOR: //don't move, hit a wall
				break;
			}
	
			break;

		case NORTH:
			next = m->GetGridContents(GetX(), GetY()-1);
			switch(next) //checks the next grid spot
			{
			case PELLET:
				//remove pellet from maze
				m->SetGridContents(GetX(), GetY()-1, EMPTY);
				//play PAC_SOUND_EAT
				SoundFX::playNachManSound(PAC_SOUND_SMALL_EAT);
				//increment score
				m_score += 10;
				//move nachman north
				SetY(GetY() - 1);
				break;
			case POWERPELLET:
				//remove pellet from maze
				m->SetGridContents(GetX(), GetY()-1, EMPTY);
				//play pacsound
				SoundFX::playNachManSound(PAC_SOUND_BIG_EAT);
				//increment score
				m_score += 100;
				//change states of monster
				if (getWorld()->GetLevel() <= 8)
					nVulnerableTicks = 100 - ((getWorld()->GetLevel()) * 10);
				else
					nVulnerableTicks = 20;
				for (int i = 0; i < NUM_MONSTERS; i++)
				{
					if (getWorld()->GetMonster(i)->getCurrentState() == normal || getWorld()->GetMonster(i)->getCurrentState() == vulnerable)
					{
						getWorld()->GetMonster(i)->setCurrentState(vulnerable); //if the monsters are currently normal/vulnerable, sets them to vulnerable
						getWorld()->GetMonster(i)->setVulnerableCount(nVulnerableTicks);
					}
				}
				//move nachman north
				SetY(GetY() - 1);
				break;
	
			case EMPTY:
				SetY(GetY() - 1);//move nachman
				break;
			case WALL:
			case CAGEDOOR: //don't move, hit a wall
				break;
			}
	
			break;
	
		case SOUTH:
			next = m->GetGridContents(GetX(), GetY()+1);
			switch(next) //checks the next grid spot
			{
			case PELLET:
				//remove pellet from maze
				m->SetGridContents(GetX(), GetY()+1, EMPTY);
				//play PAC_SOUND_EAT
				SoundFX::playNachManSound(PAC_SOUND_SMALL_EAT);
				//increment score
				m_score += 10;
				//move nachman south
				SetY(GetY() + 1);
				break;
			case POWERPELLET:
				//remove pellet from maze
				m->SetGridContents(GetX(), GetY()+1, EMPTY);
				//play pacsound
				SoundFX::playNachManSound(PAC_SOUND_BIG_EAT);
				//increment score
				m_score += 100;
				//change states of monster
				if (getWorld()->GetLevel() <= 8)
					nVulnerableTicks = 100 - ((getWorld()->GetLevel()) * 10);
				else
					nVulnerableTicks = 20;
				for (int i = 0; i < NUM_MONSTERS; i++)
				{
					if (getWorld()->GetMonster(i)->getCurrentState() == normal || getWorld()->GetMonster(i)->getCurrentState() == vulnerable)
					{
						getWorld()->GetMonster(i)->setCurrentState(vulnerable); //if the monsters are currently normal/vulnerable, sets them to vulnerable
						getWorld()->GetMonster(i)->setVulnerableCount(nVulnerableTicks);
					}
				}
				//move nachman south
				SetY(GetY() + 1);
				break;
			case EMPTY:
				SetY(GetY() + 1);//move nachman
				break;
			case WALL:
			case CAGEDOOR: //don't move, hit a wall
				break;
			}
	
			break;

		case NONE:
		default:
			break; //don't move if user hasn't inputted direction yet
	}

		//need to check if NachMan has killed itself by moving onto a monster square
	for (int i = 0; i < NUM_MONSTERS; i++)
	{
		if (GetX() == getWorld()->GetMonster(i)->GetX() && GetY() == getWorld()->GetMonster(i)->GetY())
		{
			if (getWorld()->GetMonster(i)->getCurrentState() == vulnerable) //monster is edible
			{
				incrementScore(1000); //1000 points for eating monster
				getWorld()->GetMonster(i)->setCurrentState(monsterdie); //monster is is dead
				SoundFX::playNachManSound(PAC_SOUND_BIG_EAT); //plays munch sound
			}
			else if (getWorld()->GetMonster(i)->getCurrentState() == normal) //monster is not edible
				setAlive(false); //nm dies
		}
	}
}

bool NachMan::isAlive()
{
	return m_alive; 
}

void NachMan::setAlive(bool state)
{
	m_alive = state;
}

void NachMan::setLives(int n)
{
	m_lives = n;
}

void NachMan::setScore(int n)
{
	m_score = n;
}



//Monster implementations

Monster::Monster()
{
	m_currentState = normal;
	m_vulnerableCount = 0;
	m_currentTargetX = 0;
	m_currentTargetY = 0;
}

void Monster::DoSomething()
{
	//The generic monster implementation of DoSomething() moves the monster one
	//square towards its target.

	bool hasMoved = false; //tracks whether the monster has moved this turn
	
	if (getDirection() == NONE) //if the current direction is set to NONE
	{
		int d = rand() % 2;
		if (d == 0)
			setDirection(WEST); //the monsters move back and forth before exiting cage
		else
			setDirection(EAST);
	}

	if (getTargetX() != GetX()) //if the monster is not in the same column as its target
	{
		if (getTargetX() > GetX()) //if the target column is to the east
		{
			if (getWorld()->GetMaze()->GetGridContents(GetX()+1, GetY()) != WALL && getDirection() != WEST)
				//if there is no wall to the east, and the monster is not moving west
			{
				SetX(GetX()+1); //move east
				setDirection(EAST);
				hasMoved = true;
			}
		}

		else //the target column is to the west
		{
			if (getWorld()->GetMaze()->GetGridContents(GetX()-1, GetY()) != WALL && getDirection() != EAST)
				//if there is no wall to the west, and the monster is not moving east
			{
				SetX(GetX()-1); //move west
				setDirection(WEST);
				hasMoved = true;
			}
		}
	}
	if (getTargetY() != GetY() && !hasMoved) //if the target is in a different row
	{
		if (getTargetY() < GetY()) //if the target row is to the north
		{
			if (getWorld()->GetMaze()->GetGridContents(GetX(), GetY()-1) != WALL && getDirection() != SOUTH)
				//if there is no wall to the north, and the monster is not moving south
			{
				SetY(GetY()-1); //move north
				setDirection(NORTH);
				hasMoved = true;
			}
		}

		else //if the target row is to the south
		{
			if (getWorld()->GetMaze()->GetGridContents(GetX(), GetY()+1) != WALL && getDirection() != NORTH)
				//if there is no wall to the south, and the monster is not moving north
			{
				if (getWorld()->GetMaze()->GetGridContents(GetX(), GetY()+1) == CAGEDOOR)
				{
					if (getCurrentState() == returntohome)
					{
						SetY(GetY()+1); //move south
						setDirection(SOUTH);
						hasMoved = true;
					}
					else
						; //this prevents the monsters from going back into the cage unless they are returning to home
				}
				else
				{
					SetY(GetY()+1); //move south
					setDirection(SOUTH);
					hasMoved = true;
				}
			}
		}
	}

	if (! hasMoved) //if the monster still has not moved
	{

		if (getWorld()->GetMaze()->GetGridContents(GetX(), GetY()-1) != WALL && getDirection() != SOUTH)
				//if there is no wall to the north, and the monster is not moving south
		{
			SetY(GetY()-1); //move north
			setDirection(NORTH);
			hasMoved = true;
		}

		else if (getWorld()->GetMaze()->GetGridContents(GetX()+1, GetY()) != WALL && getDirection() != WEST)
			//if there is no wall to the east, and the monster is not moving west
		{
			SetX(GetX()+1); //move east
			setDirection(EAST);
			hasMoved = true;
		}
		

		else if (getWorld()->GetMaze()->GetGridContents(GetX()-1, GetY()) != WALL && getDirection() != EAST)
			//if there is no wall to the west, and the monster is not moving east
		{
			SetX(GetX()-1); //move west
			setDirection(WEST);
			hasMoved = true;
		}
		
		else if (getWorld()->GetMaze()->GetGridContents(GetX(), GetY()+1) != WALL && getDirection() != NORTH)
				//if there is no wall to the south, and the monster is not moving north
		{
			if (getWorld()->GetMaze()->GetGridContents(GetX(), GetY()+1) == CAGEDOOR)
			{
				if (getCurrentState() == returntohome)
				{
					SetY(GetY()+1); //move south
					setDirection(SOUTH);
					hasMoved = true;
				}
				else
					; //this prevents the monsters from going back into the cage unless they are returning to home
			}
			else
			{
				SetY(GetY()+1); //move south
				setDirection(SOUTH);
				hasMoved = true;
			}
		}
	
		else
		{
		//if after all this the monster still hasn't moved, it will have to turn around
			if (getWorld()->GetMaze()->GetGridContents(GetX()+1, GetY()) != WALL) //east
			{
				SetX(GetX()+1);
				setDirection(EAST);
				hasMoved = true;
			}
		
			else if (getWorld()->GetMaze()->GetGridContents(GetX()-1, GetY()) != WALL)//west
			{
				SetX(GetX()-1);
				setDirection(WEST);
				hasMoved = true;
			}
		
			else if (getWorld()->GetMaze()->GetGridContents(GetX(), GetY()+1) != WALL &&
					  getWorld()->GetMaze()->GetGridContents(GetX(), GetY()+1) != CAGEDOOR)//south
			{
				SetY(GetY()+1);
				setDirection(SOUTH);
				hasMoved = true;
			}
		
			else if (getWorld()->GetMaze()->GetGridContents(GetX(), GetY()-1) != WALL)//north
			{
				SetY(GetY()-1);
				setDirection(NORTH);
				hasMoved = true;
			}	
		}
	}
}

void Monster::setTargetX(int x)
{
	m_currentTargetX = x;
}

void Monster::setTargetY(int y)
{
	m_currentTargetY = y;
}

int Monster::getTargetX()
{
	return m_currentTargetX;
}

int Monster::getTargetY()
{
	return m_currentTargetY;
}

void Monster::setCurrentState(MonsterStates newState)
{
	m_currentState = newState;
}

int Monster::getCurrentState()
{
	return m_currentState;
}

void Monster::setVulnerableCount(int count)
{
	m_vulnerableCount = count;
}

int Monster::getVulnerableCount()
{
	return m_vulnerableCount;
}

void Monster::decrementVulnerableCount()
{
	m_vulnerableCount--;
}

void Monster::Vuln()
{
	//vulnerable behavior
	int x = rand() % MAZE_WIDTH;
	int y = rand() & MAZE_HEIGHT;
	setTargetX(x);
	setTargetY(y);
	Monster::DoSomething(); //moves

	if (GetX() == getWorld()->GetNachMan()->GetX() && GetY() == getWorld()->GetNachMan()->GetY())
		//if monster has hit NM
	{
		getWorld()->GetNachMan()->incrementScore(1000); //1000 points for eating monster
		setCurrentState(monsterdie); //monster is is dead
		SoundFX::playNachManSound(PAC_SOUND_BIG_EAT); //plays munch sound
	}

	decrementVulnerableCount();
	if (getVulnerableCount() == 0) //if monst isn't vulnerable anymore
		setCurrentState(normal);
}

void Monster::MonsterDie()
{
	setCurrentState(returntohome);
}

void Monster::ReturnToHome()
{
	int x; int y; 
	if (getWorld()->GetMaze()->GetNextCoordinate(GetX(), GetY(), x, y)) //if the monster has not yet reached home
	{
		setTargetX(x);
		setTargetY(y);
		Monster::DoSomething();
	}
	
	else
	{
		setVulnerableCount(0); //resets the vulnerable count
		setCurrentState(normal); //the monster has made it back home and returns to normal
		setDirection(NORTH); //they get back out of the cage much more quickly
	}
}

//Inky
Inky::Inky(World* world, int x, int y)
{
	int v = rand() % 100;
	setChase(! (v >= 81)); //inky doesn't chase 20% of the time
	resetInkyCounter();
	setWorld(world);
	SetX(x);
	SetY(y);
}

Inky::~Inky()
{
	//destructor
}

void Inky::DoSomething()
{
	if (getCurrentState() == normal)
		//normal behavior is different for Inky
		Normal();

	else if (getCurrentState() == vulnerable)
		Vuln();

	else if (getCurrentState() == monsterdie)
		MonsterDie();

	else if (getCurrentState() == returntohome)
		ReturnToHome();
}

int Inky::getMyID()
{
	return ITEM_MONSTER1;
}

int Inky::getInkyCounter()
{
	return m_InkyCounter;
}

void Inky::resetInkyCounter()
{
	m_InkyCounter = 10;
}

bool Inky::inkyChase()
{
	return m_chase;
}

void Inky::setChase(bool b)
{
	m_chase = b;
}

colors Inky::GetDisplayColor()
{
	if (getCurrentState() == normal)
		return RED;
	else if (getCurrentState() == vulnerable)
		return LIGHTBLUE;
	else //(getCurrentState() == returntohome || getCurrentState() == monsterdie)
		return LIGHTGRAY;
}

void Inky::Normal()
{
	if (getInkyCounter() == 0) //time to reevaluate inky's behavior
		{
			int v = rand() % 100;
			setChase(! (v >= 81)); //inky doesn't chase 20% of the time
			resetInkyCounter();
		}


		if (inkyChase()) //if he feels like chasing
		{
			setTargetX(getWorld()->GetNachMan()->GetX());
			setTargetY(getWorld()->GetNachMan()->GetY()); //sets the target to nachman's current location
		}

		else //feels like a CRUISE
		{
			int x = rand() % MAZE_WIDTH;
			int y = rand() & MAZE_HEIGHT;
			setTargetX(x);
			setTargetY(y);
		}

		Monster::DoSomething();

		if (GetX() == getWorld()->GetNachMan()->GetX() && GetY() == getWorld()->GetNachMan()->GetY())
			//if Inky has hit NachMan
			getWorld()->GetNachMan()->setAlive(false);
}





//Stinky
Stinky::Stinky(World* world, int x, int y)
{
	setWorld(world);
	SetX(x);
	SetY(y);
	//constructor
}

Stinky::~Stinky()
{
	//destructor
}

void Stinky::DoSomething()
{
	if (getCurrentState() == normal)
		Normal();

	else if (getCurrentState() == vulnerable)
		Vuln();

	else if (getCurrentState() == monsterdie)
		MonsterDie();

	else if (getCurrentState() == returntohome)
		ReturnToHome();
}

int Stinky::getMyID()
{
	return ITEM_MONSTER2;
}

colors Stinky::GetDisplayColor()
{
	if (getCurrentState() == normal)
		return LIGHTGREEN;
	else if (getCurrentState() == vulnerable)
		return LIGHTBLUE;
	else //(getCurrentState() == returntohome || getCurrentState() == monsterdie)
		return LIGHTGRAY;
}

void Stinky::Normal()
{
	int nmX = getWorld()->GetNachMan()->GetX();
	int nmY = getWorld()->GetNachMan()->GetY(); //grabs the current position of NM
	if (abs(GetX() - nmX) <= 5 && abs(GetY() - nmY) <= 5) //if Stinky smells NM
	{
		setTargetX(nmX);
		setTargetY(nmY);
	}
	else //can't smell
	{
		int x = rand() % MAZE_WIDTH;
		int y = rand() & MAZE_HEIGHT;
		setTargetX(x);
		setTargetY(y); //just sets a random target
	}

	Monster::DoSomething(); //move

	if (GetX() == getWorld()->GetNachMan()->GetX() && GetY() == getWorld()->GetNachMan()->GetY())
		//if stinky has hit NachMan
		getWorld()->GetNachMan()->setAlive(false);
}

//Dinky
Dinky::Dinky(World* world, int x, int y)
{
	setWorld(world);
	SetX(x);
	SetY(y);
}

Dinky::~Dinky()
{
	//destructor
}

void Dinky::DoSomething()
{
	if (getCurrentState() == normal)
		Normal();

	else if (getCurrentState() == vulnerable)
		Vuln();

	else if (getCurrentState() == monsterdie)
		MonsterDie();

	else if (getCurrentState() == returntohome)
		ReturnToHome();
}

int Dinky::getMyID()
{
	return ITEM_MONSTER3;
}

colors Dinky::GetDisplayColor()
{
	if (getCurrentState() == normal)
		return LIGHTMAGENTA;
	else if (getCurrentState() == vulnerable)
		return LIGHTBLUE;
	else // (getCurrentState() == returntohome || getCurrentState() == monsterdie)
		return LIGHTGRAY;
}

void Dinky::Normal()
{
	int nmX = getWorld()->GetNachMan()->GetX();
	int nmY = getWorld()->GetNachMan()->GetY(); //gets nachman's current location

	bool canSmell = false; //tracks if dinky can smell NM

	if (GetY() == nmY) //if they are in the same row
	{
		if (nmX > GetX()) //if NM is east of Dinky
		{
			int i = GetX();
			while (i != nmX)
			{
				if (getWorld()->GetMaze()->GetGridContents(i, GetY()) == WALL)
					break;
				i++;
			}
			if (i == nmX)
				canSmell = true; //no walls between Dinky and NM
		}

		else //NMX < GetX(); NM is west of dinky
		{
			int i = nmX;
			while (i != GetX())
			{
				if (getWorld()->GetMaze()->GetGridContents(i, GetY()) == WALL)
					break;
				i++;
			}
			if (i == GetX())
				canSmell = true; //no walls
		}
	}
		
	else if (GetX() == nmX) //same col
	{
		if (nmY > GetY()) //if NM is below Dinky
		{
			int i = GetY();
			while (i != nmY)
			{
				if (getWorld()->GetMaze()->GetGridContents(GetX(), i) == WALL)
					break;
				i++;
			}
			if (i == nmY)
				canSmell = true; //no walls between Dinky and NM
		}

		else //nmY < GetY(); nm is above dinky
		{
			int i = nmY;
			while (i != GetY())
			{
				if (getWorld()->GetMaze()->GetGridContents(GetX(), i) == WALL)
					break;
				i++;
			}
			if (i == GetY())
				canSmell = true; //no walls
		}
	}

	if (canSmell == true) //if dinky can smell NM
	{
		setTargetX(nmX);
		setTargetY(nmY);
	}
	else //can't smell; random target
	{
		int x = rand() % MAZE_WIDTH;
		int y = rand() % MAZE_HEIGHT;
		setTargetX(x);
		setTargetY(y);
	}

	Monster::DoSomething();

	if (GetX() == getWorld()->GetNachMan()->GetX() && GetY() == getWorld()->GetNachMan()->GetY())
		//if dinky has hit NachMan
		getWorld()->GetNachMan()->setAlive(false);
			
}

//Clyde
Clyde::Clyde(World* world, int x, int y)
{
	setWorld(world);
	SetX(x);
	SetY(y);
}

Clyde::~Clyde()
{
	//destructor
}

void Clyde::DoSomething()
{
	if (getCurrentState() == normal) //normal behavior
		Normal();

	else if (getCurrentState() == vulnerable)
		Vuln();

	else if (getCurrentState() == monsterdie)
		MonsterDie();

	else if (getCurrentState() == returntohome)
		ReturnToHome();
}		

int Clyde::getMyID()
{
	return ITEM_MONSTER4;
}

colors Clyde::GetDisplayColor()
{
	if (getCurrentState() == normal)
		return LIGHTCYAN;
	else if (getCurrentState() == vulnerable)
		return LIGHTBLUE;
	else // (getCurrentState() == returntohome || getCurrentState() == monsterdie)
		return LIGHTGRAY;
}

void Clyde::Normal()
{
	int x = rand() % MAZE_WIDTH;
	int y = rand() & MAZE_HEIGHT;
	setTargetX(x);
	setTargetY(y);
	Monster::DoSomething(); //moves

	if (GetX() == getWorld()->GetNachMan()->GetX() && GetY() == getWorld()->GetNachMan()->GetY())
	//if Clyde has hit NachMan
		getWorld()->GetNachMan()->setAlive(false);
}

void Clyde::Vuln()
{
	int nmX = getWorld()->GetNachMan()->GetX();
	int nmY = getWorld()->GetNachMan()->GetY(); //finds nachman's position

	if (nmX < 10 && nmY < 7) //if NM is in the upper left quad
	{
		setTargetX(MAZE_WIDTH);
		setTargetY(MAZE_HEIGHT); //set target to the bottom right
	}
	
	else if (nmX > 10 && nmY < 7) //upper right
	{
		setTargetX(0);
		setTargetY(MAZE_HEIGHT); //set target to bottom left
	}

	else if (nmX < 10 && nmY > 7) //bot left
	{
		setTargetX(MAZE_WIDTH);
		setTargetY(0); //sets target to upper right
	}

	else //bot right
	{
		setTargetX(0);
		setTargetY(0); //top left
	}

	Monster::DoSomething();

	if (GetX() == getWorld()->GetNachMan()->GetX() && GetY() == getWorld()->GetNachMan()->GetY())
		//if Clyde has hit NachMan
	{
		getWorld()->GetNachMan()->incrementScore(1000); //1000 points for eating clyde
		setCurrentState(monsterdie); //clyde is dead
		SoundFX::playNachManSound(PAC_SOUND_BIG_EAT); //plays munch sound
	}

	decrementVulnerableCount();
	if (getVulnerableCount() == 0) //if clyde isn't vulnerable anymore
		setCurrentState(normal);
}
