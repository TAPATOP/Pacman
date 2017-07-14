#pragma once
#include "Actor.h"
class Bot :
	public Actor
{
public:
	Bot();
	Bot(int x, int y, int dx, int dy, float movementSpeed, unsigned int attackRange);

	int move();
	void die();
	
	void setIsVulnerable(bool);
	void setIsGhost(bool);

	bool getIsVulnerable();
	bool getIsGhost();

	~Bot();
private:
	bool isVulnerable;
	bool isGhost;
	unsigned int attackRange;
};
