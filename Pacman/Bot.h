#pragma once
#include <cstdlib>
#include <ctime>

#include"Actor.h"
#include"BotStack.h"

class Bot :
	public Actor
{
public:
	Bot();
	Bot(int botID, unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar);
	
	void setIsVulnerable(bool);
	void setIsGhost(bool);
	void setID(int);
	void setCheckMe(bool);

	bool getIsVulnerable();
	bool getIsGhost();
	int getID();
	bool getCheckMe();
	int getVulnerabilityTimer();

	ItskoVector2i move();
	void die();
	void deleteStack();

	~Bot();
private:
	void pickRandomDirection(bool mustBeOppositeToOldDXDY = 1);
	void cornerSolver(); // adjusts DX and DY in such way so the bot will traverse it properly
	void reverseDirection();

public: void findRouteToDestination(int destinationY, int destinationX);

private:
	bool isVulnerable;
	bool isGhost;

	bool checkMe = 0;

	int vulnerabilityTimer = 0;

	int botID; // I want it manually set for now

	BotStack* destinationStack;
};
