////////////
/// PLEASE NOTE THAT y IS HEIGHT AND x IS WIDTH, SO YOU'LL HAVE TO
/// USE COORDINATES AS: object[y][x]
////////////

#pragma once
#include<iostream>
#include<SFML/Graphics/Vertex.hpp>

#include"Global_Constants.cpp"
#include"ItskoVector2i.h"
#include"Map.h"

class Actor
{
public:
	Actor();
	//Actor(Actor&);
	Actor(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar);
	Actor(unsigned int y, unsigned int x, unsigned int startingY, unsigned int startingX, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar);

	void setMovementSpeed(unsigned int movementSpeed);
	void setMovementProgress(int movementProgress);
	void setX(unsigned int x, std::ostream& out = std::cout);
	void setY(unsigned int y);
	void setDX(int dx);
	void setDY(int dy);
	void setMap(Map*);
	void setDisplayChar(char c);

	int getMovementSpeed() const;
	int getMovementProgress() const;
	int getX() const;
	int getY() const;
	int getDX() const;
	int getDY() const;
	char getDisplayChar() const;

	virtual ItskoVector2i move() = 0;
	virtual void die() = 0;
	virtual void resetPosition();

	virtual ~Actor(); 
protected:
		bool canMove() const;
		bool canMove(ItskoVector2i& newDirections) const;// decides whether the actor can move with the current x, y, dx and dy
		virtual ItskoVector2i executeMoving(); // moves the actor according to x, y, dx, dy and his speed
protected:
	Map* map; // all Actors will use the same map to traverse
private:
	unsigned int x; // how wide
	unsigned int y; // how high
	
	unsigned int startingX;
	unsigned int startingY;

	int dx; // horizontal movement direction, supposed to be either -1, 0 or 1, not decided on it yet tho
	int dy; // vertical movement direction, supposed to be either -1, 0 or 1, not decided on it yet tho

	int movementSpeed; // lower is faster
	int movementProgress = 0; // should always be lower than movementSpeed

	char displayChar;
	//Node* lastVisitedNode; // future implementation
protected:
	static const unsigned int maxActors = 10;
	static Actor* allActors[maxActors];
	static int allActorsCount;
};
