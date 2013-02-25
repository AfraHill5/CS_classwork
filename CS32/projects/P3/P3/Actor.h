#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "testdefines.h"
#include "BGIgraphics.h"
#include "GraphManager.h"

/*		tree structure:

			ACTOR
			/   \
		N.MAN    MONSTER
				       \
						INKY
						STINKY
						DINKY
						CLYDE

*/

class World;
class Maze; //prototypes

class Actor 
{
public:
	//functions:
	virtual int		GetX();					//returns X coord of actor
	virtual int		GetY();					//returns Y coord of actor
	virtual void	SetX(int newXCoord);	//sets X coord of actor
	virtual void	SetY(int newYCoord);	//sets Y coord of actor
	virtual void	DoSomething() = 0;		//tells actor to take an action
	virtual colors	GetDisplayColor() = 0;	//gets the color to display onscreen
	virtual World*	getWorld();				//returns the current world of the actor
	virtual void	setWorld(World* w);		//used to set the m_world to the input
	virtual void	setDirection(Direction d = NONE); //sets the direction
	virtual Direction getDirection();		//returns the direction
	virtual int		getMyID() = 0;			/*returns the ID of each actor:
											Inky =		ITEM_MONSTER1
											Stinky =	ITEM_MONSTER2
											Dinky =		ITEM_MONSTER3
											Clyde =		ITEM_MONSTER4
											NachMan =	ITEM_NACHMAN	*/
	//housekeeping:
	Actor(); 
	virtual ~Actor();

private:
	Direction	m_direction;			//direction the actor is facing
	int			m_x;
	int			m_y; //actor positions
	World*		m_world; //pointer back to the actors' current world
};

class NachMan : public Actor
{
public:
	//functions:
	int			GetNumLivesLeft();		//returns number of lives remaining
	void		DecrementNumLives();	//reduces number of lives by one
	int			GetScore();				//returns the current score
	void		incrementScore(int n);	//increments score by n
	colors		GetDisplayColor();		//returns the color that should be used by the maze class
	int			getMyID();				//returns the id of the NachMan
	void		DoSomething();			//moves NachMan
	bool		isAlive();				//returns true if NachMan is dead
	void		setAlive(bool state);	//sets NachMan to alive/dead
	void		setLives(int n = 3);	//sets the number of lives
	void		setScore(int n = 0);	//sets the score
	
	
	
	//housekeeping:
	NachMan(World* currentWorld, int X, int Y); //initialized with starting pos and pointer to world ((check syntax))
	~NachMan();

private:
	bool		m_alive;				//TRUE if alive, FALSE if dead
	int			m_lives;				//number of lives remaining for the NachMan
	int			m_score;				//current score of the NachMan
};

enum MonsterStates {vulnerable, normal, monsterdie, returntohome};

class Monster : public Actor
{
public:
	//functions:
	virtual void	DoSomething();
	virtual int		getMyID() = 0;
	virtual void	setTargetX(int x); //sets the current target
	virtual void	setTargetY(int y);
	virtual int		getTargetX(); //returns the current target value
	virtual int		getTargetY();
	virtual void	setCurrentState(MonsterStates newState); //changes the current state
	virtual int		getCurrentState(); //returns the current state 
	virtual void	setVulnerableCount(int count); //sets the vulnerable count to a new value
	virtual int		getVulnerableCount(); //returns the vulnerable count
	virtual void	decrementVulnerableCount(); //obvious
	virtual colors	GetDisplayColor() = 0;
	virtual void	Vuln(); //the default behavior for a vulnerable monster
	virtual void	Normal() = 0; //default normal behavior
	virtual void	MonsterDie(); //defualt monsterdie
	virtual void	ReturnToHome(); //default return to home


	//housekeeping:
	Monster() ;
	virtual ~Monster() {};

private:
	int				m_currentState; //vulnerable, normal, monsterdie, returntohome
	int				m_vulnerableCount;
	int				m_currentTargetX;
	int				m_currentTargetY; //the coords of the current target of the monsters
};

class Inky : public Monster
{
public:
	//functions:
	virtual void DoSomething();
	int getMyID();
	int getInkyCounter(); //returns the number of behavior ticks remaining
	void resetInkyCounter(); //resets the number of behavior ticks
	bool inkyChase(); //returns true if inky is chasing nachman
	void setChase(bool b); //sets chase status
	colors GetDisplayColor();
	void Normal(); //Inky's different behavior

	//housekeeping:
	Inky(World* world, int x, int y);
	~Inky();

private:
	int m_InkyCounter; //inky's counter of behavior ticks remaining
	bool m_chase; //true if inky feels like chasing
};

class Stinky : public Monster
{
public:
	//functions:
	virtual void DoSomething();
	int getMyID();
	colors GetDisplayColor();
	void Normal(); //stinky has different normal behavior

	//housekeeping:
	Stinky(World* world, int x, int y);
	~Stinky();
};

class Dinky : public Monster
{
public:
	//functions:
	virtual void DoSomething();
	int getMyID();
	colors GetDisplayColor();
	void Normal(); //dinky has different normal behavior

	//housekeeping:
	Dinky(World* world, int x, int y);
	~Dinky();
};

class Clyde : public Monster
{
public:
	//functions:
	virtual void DoSomething();
	int getMyID();
	colors GetDisplayColor();
	void Normal(); //clyde has different normal behavior
	void Vuln(); //he also has strange Vulnerable behavior

	//housekeeping:
	Clyde(World* world, int x, int y);
	~Clyde();
};


#endif // #ifndef _ACTOR_H_
