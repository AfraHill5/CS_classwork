#include "StudentWorld.h"
#include "actor.h"
#include <algorithm> //for min, max

StudentWorld::StudentWorld()
{
	m_counter = 0;
}

StudentWorld::~StudentWorld()
{
	cleanUp();
}

void StudentWorld::init()
{
	int randX, randY, testX, testY, numMushrooms;  //random value
	Mushroom* m;
	if (testParamsProvided())
		numMushrooms = getTestParam(TEST_PARAM_STARTING_MUSHROOMS);
	else
		numMushrooms = 25;
	//add the number of shrooms specified
	for (int i = 0; i < numMushrooms; i++)
	{
		randX = rand() % 30; //random xval from 0 to 29
		randY = ((rand() % 18)+1); //random yval from 1 to 18

		for (int j = 0; j < m_actors.size(); j++) //checking to make sure
		{										//mushrooms arent duplicates
			m_actors[j]->getLocation(testX, testY);
			if ((testX == randX) && (testY == randY)) //if a mushroom already exists
			{
				j = -1; //try another random number and start over
				randX = rand() % 30; //random xval from 0 to 29
				randY = ((rand() % 18)+1); //random yval from 1 to 18
				continue;
			}
		}
		//if no other mushrooms already exist at the point, add and continue
		m = new Mushroom(randX, randY, this);
		setActor(m);
	}

	//add player
	Player* p = new Player(this);
	setPlayer(p);
}

int StudentWorld::move()
{
	m_counter++; //tracks the amount of moves
	addEnemies();

	int size = m_actors.size();

	m_player->doSomething(); //moves the player

	//move each actor
	for (int i = 0; i < size; i++)
	{
		if (m_actors[i]->isAlive())
		{
			m_actors[i]->doSomething();
		}
	}

	removeDeadGameObjects();

	if (!m_player->isAlive()) //if the player died during this tick
		return GWSTATUS_PLAYER_DIED;
	else //player lived, continue
		return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	//player died so clean up the screen
	while (m_actors.size() > 0)
	{
		delete m_actors.back();
		m_actors.pop_back();
	}
	delete m_player;
}

void StudentWorld::addEnemies()
{
	if (testParamsProvided())
	{
		if (m_counter > 0 && 
				m_counter % getTestParam(TEST_PARAM_CENT_CHANCE_INDEX))
			addInsect(IID_SCENTIPEDE_SEGMENT);
		if (m_counter > 0 &&
				m_counter % getTestParam(TEST_PARAM_SPIDER_CHANCE_INDEX))
			addInsect(IID_SPIDER);
		if (m_counter > 0 &&
				m_counter % getTestParam(TEST_PARAM_FLEA_CHANCE_INDEX))
			addInsect(IID_FLEA);
		if (m_counter > 0 &&
				m_counter % getTestParam(TEST_PARAM_SCORPION_CHANCE_INDEX))
			addInsect(IID_SCORPION);
	}

	else //no test params provided
	{
		int currentLevel = (getPlayerScore()) / 500; //provided algorithm
		
		int numScentSegs = 0;
		int numOtherInsects = 0;

		//counting each type of insect in the game
		for (int i = 0; i < numActors(); i++)
		{
			if (m_actors[i]->getID() == IID_SCENTIPEDE_SEGMENT)
				numScentSegs++;
			else if (m_actors[i]->getID() == IID_SPIDER || 
					 m_actors[i]->getID() == IID_FLEA	||
					 m_actors[i]->getID() == IID_SCORPION )
				numOtherInsects++;
			//ignore others
		}

		//scentipede adding algorithm
		if (numScentSegs >= std::min(20, (currentLevel+1) *3)) //minimum of 20, (cL+1)*3
			;//do NOT add a scentipede
		else if (numScentSegs == 0)
		{
			int scenChance = rand() % 20;
			if (scenChance == 0) //5% chance to add a segment
				addInsect(IID_SCENTIPEDE_SEGMENT);
		}
		else if (numScentSegs > 0)
		{
			int scenChance = rand() % (std::max(300-(30*currentLevel), 50));
			//smaller chance related to level
			if (scenChance == 0)
				addInsect(IID_SCENTIPEDE_SEGMENT);
		} 
		
		//other insect adding algorithm
		if (numOtherInsects < ((currentLevel / 2) + 1))
		//don't add any other insects if there are already many
		{
			int fChance = rand() % (std::max(300-(currentLevel*30), 100));
			int spChance = rand() % (std::max(350-(currentLevel*30), 100));
			int scorChance = rand() % (std::max(400-(currentLevel*30), 100));
			if (fChance == 0)
				addInsect(IID_FLEA);
			else if (spChance == 0)
				addInsect(IID_SPIDER);
			else if (scorChance == 0)
				addInsect(IID_SCORPION);
		}
	}
}

void StudentWorld::addInsect(int id)
{
	if (id == IID_SCENTIPEDE_SEGMENT)
	//scentipede code
	{
		
		int numSegments = (rand() % 6) + 6;
		//num segments is btwn 6 and 12
		for (numSegments; numSegments > 0; numSegments--)
		{
			ScentipedeSeg* s;
			s = new ScentipedeSeg(numSegments, GARDEN_HEIGHT-1, this);
			setActor(s);
		}
	}

	else if (id == IID_FLEA)
	{
		int xLoc = (rand() % GARDEN_WIDTH);
		int yLoc = GARDEN_HEIGHT-1;
		Flea* f;
		f = new Flea(xLoc, yLoc, this);
		setActor(f);
	}

	else if (id == IID_SPIDER)
	{
		int xLoc;
		int side = (rand() % 2);
		if (side == 0) //left
			xLoc = 0;
		else //right
			xLoc = GARDEN_WIDTH-1;

		int yLoc = (rand() % 15) + 5;
		Spider* sp;
		sp = new Spider(xLoc, yLoc, this);
		setActor(sp);
	}
	else if (id == IID_SCORPION)
	{
		int xLoc = 0;
		int yLoc = (rand() % 16) + 4;
		Scorpion* scor;
		scor = new Scorpion(xLoc, yLoc, this);
		setActor(scor);
	}
	else //error
	{}
}

void StudentWorld::removeDeadGameObjects()
{
	int size = m_actors.size();
	for (int i = 0; i < size; i++)
	{
		if (!m_actors[i]->isAlive()) //if current actor is dead
		{
			delete m_actors[i];
			m_actors.erase(m_actors.begin() + i);
			size--;
			i--;
		}
	}
}

bool StudentWorld::mushroomOnSquare(int x, int y, int& index)
{
	int aX,aY;
	for (int i = 0; i < numActors(); i++)
	{ //checks if there are any mushrooms on the current square
		getActor(i)->getLocation(aX,aY);
		if ((aX == x) && (aY == y) && 
			((getActor(i)->getID() == IID_MUSHROOM) ||
			 (getActor(i)->getID() == IID_POISON_MUSHROOM)))
			 //if the actor has the same coordinates and is a type of mushroom
		{
			index = i;
			return true; //cant drop a mushroom on top of it
		}
	}
	return false;
}
		
void StudentWorld::setPlayer(Player* p)
{
	m_player = p;
}

Player* StudentWorld::getPlayer()
{
	return m_player;
}

void StudentWorld::setActor(Actor* a)
{
	m_actors.push_back(a);
}

Actor* StudentWorld::getActor(int i)
{
	return m_actors[i];
}

Actor* StudentWorld::getActorAt(int x, int y, int& id)
{
	int aX, aY;
	int i = 0;
	for (; i < numActors(); i++)
	{
		m_actors[i]->getLocation(aX, aY);
		if (x == aX && y == aY) //hit
		{
			id = m_actors[i]->getID();
			return m_actors[i];
		}
	}
	//check for player
	getPlayer()->getLocation(aX, aY);
	if (x == aX && y == aY)
	{
		id = IID_PLAYER;
		return m_player;
	}

	return NULL; //not present in the current actors
}

int StudentWorld::numActors()
{
	return m_actors.size();
}