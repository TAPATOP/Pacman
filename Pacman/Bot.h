#pragma once
#include<cstdlib>
#include<ctime>

#include "Actor.h"

class Bot :
	public Actor
{
public:
	Bot();
	Bot(int botID, unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, unsigned int attackRange, Map* map);

	void setIsVulnerable(bool);
	void setIsGhost(bool);
	void setID(int);

	bool getIsVulnerable();
	bool getIsGhost();
	int getID();

	sf::Vector2f move();
	void die();

	~Bot();
protected:
	void pickRandomDirection(bool notAtInit = 1);
	void cornerSolver(); // adjusts DX and DY in such way so the bot will traverse it properly
	void reverseDirection();
private:
	bool isVulnerable;
	bool isGhost;
	unsigned int attackRange;

	int botID; // I want it manually set for now
};
