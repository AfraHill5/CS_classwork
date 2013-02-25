#ifndef _ACTOR_H_

#define _ACTOR_H_

#include "GraphObj.h"
#include "GameConstants.h"

#include "GameWorld.h"

class StudentWorld; //prototype for header

class Actor : public GraphObject
{
public:
	Actor(int id, StudentWorld* world);
	virtual ~Actor();

	virtual void doSomething() = 0;
	virtual void isAttacked(Actor* attacker) = 0;
	virtual int isAlive() = 0;

	StudentWorld* getWorld();

private:
	StudentWorld* m_world;
};

class Player : public Actor
{
public:
	Player(StudentWorld* world);
	virtual ~Player();

	virtual void doSomething();
	virtual void isAttacked(Actor* attacker);
	void tryMove(int x, int y);

	virtual int isAlive();

private:
	bool m_alive;
	bool m_firedLastTurn; //used to prevent player from rapid-firing
};

class Insect : public Actor
{
public:
	Insect(int id, int x, int y, StudentWorld* world);
	virtual ~Insect();

	
	virtual int	 isAlive();
	void		setAlive(bool a);

	virtual void doSomething() = 0;
	virtual void isAttacked(Actor* attacker) = 0;
private:
	bool m_alive;
};

class ScentipedeSeg : public Insect
{
public: 
	ScentipedeSeg(int x, int y, StudentWorld* world);
	virtual ~ScentipedeSeg();

	virtual void doSomething();
	virtual void isAttacked(Actor* attacker);
	bool isPoisoned();
private:
	char m_horizMove; //'r' or 'l'
	char m_nextVert;  //'u' or 'd'
	bool m_isPoisoned;
};

class Spider : public Insect
{
public:
	Spider(int x, int y, StudentWorld* world);
	virtual ~Spider();

	virtual void doSomething();
	virtual void isAttacked(Actor* attacker);
private:
	int m_r;
	char m_vertDir; //'u' or 'd'
	char m_horizDir; //'l' or 'r'
	bool m_restTick; //rests every other tick
};

class Scorpion : public Insect
{
public:
	Scorpion(int x, int y, StudentWorld* world);
	virtual ~Scorpion();

	virtual void doSomething();;
	virtual void isAttacked(Actor* attacker);
private:

};

class Flea : public Insect
{
public:
	Flea(int x, int y, StudentWorld* world);
	virtual ~Flea();

	virtual void doSomething();
	virtual void isAttacked(Actor* attacker);
private:

};

class ActorWLives : public Actor
{
public:
	ActorWLives(int id, int x, int y, StudentWorld* world);
	virtual ~ActorWLives();

	void setLives(int l);
	int getLives();
	virtual int isAlive();

	virtual void doSomething() = 0;
	virtual void isAttacked(Actor* attacker) = 0;
private:
	int m_lives;
};

class Mushroom : public ActorWLives
{
public:
	Mushroom(int x, int y, StudentWorld* world);
	virtual ~Mushroom();

	virtual void doSomething();
	virtual void isAttacked(Actor* attacker);
private:
	
};

class WaterDroplet : public ActorWLives
{
public:
	WaterDroplet(int x, int y, StudentWorld* world);
	virtual ~WaterDroplet();

	virtual void doSomething();
	virtual void isAttacked(Actor* attacker);
private:
};
#endif // #ifndef _ACTOR_H_
