#pragma once
#include<cstdlib>
#include<ctime>

#include "Actor.h"

class Bot :
	public Actor
{
public:
	Bot();
	Bot(int y, int x, int dy, int dx, float movementSpeed, unsigned int attackRange, Map* map);

	void setIsVulnerable(bool);
	void setIsGhost(bool);

	bool getIsVulnerable();
	bool getIsGhost();

	bool move();
	void die();

	~Bot();
private:
	bool isVulnerable;
	bool isGhost;
	unsigned int attackRange;
};
