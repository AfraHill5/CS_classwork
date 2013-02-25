#include "actor.h"
#include "StudentWorld.h"
#include "GameController.h"

//ACTOR
Actor::Actor(int id, StudentWorld* world) : GraphObject(id)
{
	m_world = world;
}

Actor::~Actor()
{
}

StudentWorld* Actor::getWorld()
{
	return m_world;
}


//PLAYER
Player::Player(StudentWorld* world) : Actor(IID_PLAYER, world)
{
	setInitialLocation(15,0); //initial location
	displayMe(true);
	m_alive = true;
	m_firedLastTurn = false;
}

Player::~Player()
{
}

void Player::doSomething()
{
	int key, currX, currY;
	if (getWorld()->getKey(key)) //key = current key pressed by player
	{
		switch (key)   
		{
		case KEY_PRESS_LEFT_ARROW:
			getLocation(currX, currY); //gets the player's current location
			tryMove(currX-1, currY);
			break;
		
		case KEY_PRESS_DOWN_ARROW:
			getLocation(currX, currY);
			tryMove(currX, currY-1);
			break;

		case KEY_PRESS_RIGHT_ARROW:
			getLocation(currX, currY);
			tryMove(currX+1, currY);
			break;

		case KEY_PRESS_UP_ARROW:
			getLocation(currX, currY);
			tryMove(currX, currY+1);
			break;

		case KEY_PRESS_SPACE:
			if (!m_firedLastTurn) //can't fire 2 turns in a row
			{ 
				int dropletX, dropletY, id;
				getLocation(dropletX,dropletY);
				dropletY++;
				//droplet will be placed right "above" the player on the screen
				for (; dropletY < GARDEN_HEIGHT; dropletY++)
				{
					Actor* a = getWorld()->getActorAt(dropletX, dropletY, id);
					if (a != NULL) //hit something
					{
						a->isAttacked(this);
						break;
					}
					else //the square is empty, so continue 
					{
						WaterDroplet* w = new WaterDroplet(dropletX, dropletY, getWorld());
						getWorld()->setActor(w); 
						//insert a droplet into the space so the player can see where he is firing
					}
				}
				m_firedLastTurn = true;
				return;
			}
		//any other keys do nothing
		}
		
	}
	if (m_firedLastTurn) {m_firedLastTurn = false;}
}

void Player::isAttacked(Actor* attacker)
{
	switch(attacker->getID())
	{
		case IID_SCENTIPEDE_SEGMENT:
		case IID_SPIDER:
		case IID_FLEA:
		case IID_SCORPION:
			m_alive = false;
			break;
	}
			
		//player will never hit a water droplet or other player
}

void Player::tryMove(int x, int y)
{
	if (x < 0 || x >= GARDEN_WIDTH || y < 0 || y > 3)
		return; //trying to move out of bounds, not allowed
	Actor* a;
	int actorX, actorY;
	bool collision = false; //tracks whether there is a "hit"
	for (int i = 0; i < getWorld()->numActors(); i++)
	{
		a = getWorld()->getActor(i);
		a->getLocation(actorX, actorY);
		if (x == actorX && y == actorY)
		{
			collision = true;
			break; //player collided with what a points to
		}
	}

	if (!collision) //didnt hit anything, can move to the space
		moveTo(x,y);
}

int Player::isAlive()
{
	return m_alive;
}

//INSECT

Insect::Insect(int id, int x, int y, StudentWorld* world) : Actor(id, world)
{
	setInitialLocation(x, y);
	displayMe(true);
	m_alive = true;
}

Insect::~Insect()
{
}

void Insect::isAttacked(Actor* attacker)
{
	//dies
}

int Insect::isAlive()
{
	return m_alive;
}

void Insect::setAlive(bool a)
{
	m_alive = a;
}

//CENT
ScentipedeSeg::ScentipedeSeg(int x, int y, StudentWorld* world)
	: Insect(IID_SCENTIPEDE_SEGMENT, x, y, world)
{
	m_horizMove = 'r';
	m_nextVert = 'd';
	m_isPoisoned = false;
}

ScentipedeSeg::~ScentipedeSeg()
{
}

void ScentipedeSeg::doSomething()
{
	int x, y;
	getLocation(x,y);
	if (m_isPoisoned) //move vertically
	{
 		if (y == 0) //reached the bottom of the garden
			m_isPoisoned = false; //no longer poisoned, continue as normal

		else //y > 0
		{
			int id;
			Actor* a = getWorld()->getActorAt(x, y-1, id);
			if (a != NULL) //checks for something in the way
				a->isAttacked(this);
			moveTo(x, y-1);
			return;
		}
	}
	
	int newx, newy, id;
	if (m_horizMove == 'r') {newx = x+1;}
	else /* 'l' */		    {newx = x-1;}

	newy = y;

	if (newx < 0) //went off the screen, left side
		m_horizMove = 'r';
	else if (newx == GARDEN_WIDTH) //off the screen, right side
		m_horizMove = 'l';
	else
	{
		//otherwise inside the garden and can move normally
		Actor* a = getWorld()->getActorAt(newx, newy, id);
		if ((a == NULL) ||(id != IID_MUSHROOM        &&
						   id != IID_POISON_MUSHROOM &&
						   id != IID_PLAYER          &&
						   id != IID_SCENTIPEDE_SEGMENT))
			//the next space is either empty, or contains a mushroom, player, or scentipede
			//if this is the case the scentipede moves onto the square
		{
			moveTo(newx, newy);
			return;
		}

		else if (id == IID_SCENTIPEDE_SEGMENT)
		{
			if (!a->isAlive()) //if the scentipede segment has already been shot
			{
				moveTo(newx,newy); //just ignore it and move anyways
				return;
			}
		}

		else if (id == IID_PLAYER) //if the player is in the square
		{
			a->isAttacked(this);
			return;
		}

		else if (id == IID_POISON_MUSHROOM) //poisoned mushroom on square
		{
			m_isPoisoned = true;
			m_nextVert = 'd';
		}
	}
	//either hit a mushroom, the side of the screen, or another segment
	
	//need to modify newx and newy to go up rather than down
	newx = x;
	if (m_nextVert == 'u') {newy = y+1;}
	else		    /*'d'*/{newy = y-1;}

	if (newy < 0) //reached the bottom of the garden
	{
		newy = 1;
		m_nextVert = 'u';
	}
	else if (newy == GARDEN_HEIGHT) //top
	{
		newy = GARDEN_HEIGHT-2;
		m_nextVert = 'd';
	} 
   	Actor* a = getWorld()->getActorAt(newx, newy, id);
	if ((a == NULL) || id != IID_PLAYER				&&
						id != IID_MUSHROOM			&&
						id != IID_POISON_MUSHROOM	&&
						id != IID_SCENTIPEDE_SEGMENT)
	{
		moveTo(newx, newy);
		return;
	}

	if (id == IID_POISON_MUSHROOM) 
	{
		m_isPoisoned = true;
		m_nextVert = 'd';
		newx = x;
		newy = y-1;
	}
	a = getWorld()->getActorAt(newx, newy, id);
		
	if (a != NULL)
		a->isAttacked(this);

	moveTo(newx, newy);
	return;

}

void ScentipedeSeg::isAttacked(Actor* attacker)
{
	switch(attacker->getID())
	{
	case IID_SCENTIPEDE_SEGMENT:
		setAlive(false);
		break; //kill this segment, leave the last one
	case IID_PLAYER: //shot by player
		setAlive(false);
		getWorld()->increaseScore(10);
		int x, y;   
		getLocation(x,y);
		if (y < GARDEN_HEIGHT-1) 
		{
			int mushChance = rand() % 3;
			if (mushChance == 0)
			{
				Mushroom* m; 
				m = new Mushroom(x, y, getWorld());
				getWorld()->setActor(m); //add a mushroom 1/3 times
			}
		}
		break;
	} //nothing else can kill a scentipede
}

bool ScentipedeSeg::isPoisoned()
{
	return m_isPoisoned;
}

//SPIDER
Spider::Spider(int x, int y, StudentWorld* world)
	: Insect(IID_SPIDER, x, y, world)
{
	m_r = (rand() % 4) + 1; //amount the spider moves at a time varies
	m_vertDir = 'd';
	if (x == 0) //started on left side so will move right
		m_horizDir = 'r';
	else //started on right and will move left
		m_horizDir = 'l';
	m_restTick = false;
}

Spider::~Spider()
{}

void Spider::doSomething()
{
	if (m_restTick)
	{
		m_restTick = false;
		return;
	}

	int x, y;
	getLocation(x,y);

	if (m_r == 0)
	{
		if (m_vertDir == 'u') 
		{
			m_vertDir = 'd';
			m_r = (rand() % (y-1)) + 1;
		}
		else			    
		{
			m_vertDir = 'u';
			m_r = (rand() % (GARDEN_HEIGHT-y-1) + 1);
		}
		//flip the vertical direction
	}
	else
	{
		m_r--;

		int newx = x;
		int newy = y;
		//spiders move diagonally based on their horiz/vert directions
		if (m_horizDir == 'l') {newx--;}
		else				 {newx++;}

		if (m_vertDir == 'd') {newy--;}
		else				{newy++;}

		if (newx == -1 || newx == GARDEN_WIDTH)
		setAlive(false); //went off the screen

		int id;
		Actor* a = getWorld()->getActorAt(newx,newy,id);
		if (id == IID_MUSHROOM || id == IID_POISON_MUSHROOM || id == IID_PLAYER)
			a->isAttacked(this); //kills any mushroom/player in the way

		moveTo(newx,newy);
	}
	m_restTick = true;
}

void Spider::isAttacked(Actor* attacker)
{
	switch(attacker->getID())
	{
	case IID_PLAYER:
		getWorld()->increaseScore(20);
		setAlive(false);
		//only way to be killed is by player
	}
}


//SCORPION
Scorpion::Scorpion(int x, int y, StudentWorld* world)
	: Insect(IID_SCORPION, x, y, world)
{
}

Scorpion::~Scorpion()
{}

void Scorpion::doSomething()
{
	int x,y,index;
	getLocation(x,y);
	if (getWorld()->mushroomOnSquare(x,y,index))
	{
		int r = rand() % 3;
		if (r == 0)
		{
			Actor* m = getWorld()->getActor(index);
			m->setID(IID_POISON_MUSHROOM); //sets the mushroom to poison
		}
	}
	int newx = x+1;
	if (newx == GARDEN_WIDTH)
	{
		setAlive(false);
		return;
	}
	else
		moveTo(newx,y);

	int id;
	Actor* a = getWorld()->getActorAt(newx,y,id);
	if (a != NULL && id == IID_PLAYER)
		a->isAttacked(this); //if the scorpion hits the player the player dies
}

void Scorpion::isAttacked(Actor* attacker)
{
	switch(attacker->getID())
	{
	case IID_PLAYER:
		getWorld()->increaseScore(25);
		setAlive(false);
	} //scorpion can't die any other way
}

//FLEA
Flea::Flea(int x, int y, StudentWorld* world)
	: Insect(IID_FLEA, x, y, world)
{
}

Flea::~Flea()
{
}

void Flea::doSomething()
{
	int x, y, i; //i is unused, makes mushroom function work
	getLocation(x,y);
	StudentWorld* w = getWorld();

	//if it can, drops 25% of the time
	if (!(w->mushroomOnSquare(x,y,i)) && (y > 0) && (y < GARDEN_HEIGHT-1))
	{
		int mushDrop = rand() % 4; //25% chance of dropping mushroom
		if (mushDrop == 0)
		{
			Mushroom* m = new Mushroom(x,y,w);
			w->setActor(m);
		}
	}
	int newx = x;  //x never changes
	int newy = y-1;
	if (newy < 0)
		setAlive(false); //off the screen
	else
		moveTo(newx,newy);

	int aX,aY;
	w->getPlayer()->getLocation(aX,aY);
	if (newx == aX && newy == aY) //hit the player
		w->getPlayer()->isAttacked(this);
}


void Flea::isAttacked(Actor* attacker)
{
	switch(attacker->getID())
	{
	case IID_PLAYER:
		getWorld()->increaseScore(50);
		setAlive(false);
		break;
		//fleas can't be killed except by the player
	}
}

//ACTORWLIVES
ActorWLives::ActorWLives(int id, int x, int y, StudentWorld* world)
	: Actor(id, world)
{
	switch(id)
	{
	case IID_MUSHROOM:
		m_lives = 4;
		break;
	case IID_WATER_DROPLET:
		m_lives = 2;
		break;
	}
	setInitialLocation(x,y);
	displayMe(true);
}

ActorWLives::~ActorWLives()
{
}

void ActorWLives::setLives(int l)
{
	m_lives = l;
}

int ActorWLives::getLives()
{
	return m_lives;
}

int ActorWLives::isAlive()
{
	return (m_lives > 0);
}

//MUSHROOM
Mushroom::Mushroom(int x, int y, StudentWorld* world) : ActorWLives(IID_MUSHROOM, x, y, world)
{
	displayMe(true);
}

Mushroom::~Mushroom()
{
}

void Mushroom::doSomething()
{
	//mushrooms dont do much besides sit and contemplate life as a fungi
}

void Mushroom::isAttacked(Actor* attacker)
{
	switch(attacker->getID())
	{
	case IID_SCENTIPEDE_SEGMENT: //instant kill, regardless of poison
	case IID_SPIDER:
		setLives(0);
		break;
	case IID_PLAYER: //slowly drains the color from the mushroom
		getWorld()->increaseScore(1);
		setLives(getLives()-1);
		setBrightness(getBrightness() - .25); //drains the color
		break;

	}
}


//WATERDROPLET

WaterDroplet::WaterDroplet(int x, int y, StudentWorld* world)
	: ActorWLives(IID_WATER_DROPLET, x, y, world)
{
	
}

WaterDroplet::~WaterDroplet()
{
}

void WaterDroplet::doSomething()
{
	setLives(getLives()-1); //decrement lives
}

void WaterDroplet::isAttacked(Actor* attacker)
{
	switch(attacker->getID())
	{
	case IID_SCENTIPEDE_SEGMENT:
		break; //ignore

	}
}
