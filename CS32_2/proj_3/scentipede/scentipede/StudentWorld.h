#ifndef _StudentWorld_H_
#define _StudentWorld_H_

#include "GameWorld.h"
#include "actor.h" 
#include <vector>

class StudentWorld: public GameWorld
{
public:
	StudentWorld();
	virtual ~StudentWorld();

	virtual void init();
	virtual int move();
	virtual void cleanUp(); 

	void addEnemies(); //adds all insects
	void addInsect(int id); //adds 1 insect
	void removeDeadGameObjects();
	bool mushroomOnSquare(int x, int y, int& index);

	void setPlayer(Player* p);
	Player* getPlayer();

	void setActor(Actor* m);
	Actor* getActor(int i=0);
	Actor* getActorAt(int x, int y, int& id);
	int numActors();

private:
	std::vector<Actor*> m_actors; //non-player actors
	Player* m_player;
	int m_counter;
};

#endif // #ifndef _StudentWorld_H_
