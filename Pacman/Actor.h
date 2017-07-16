////////////
/// PLEASE NOTE THAT y IS HEIGHT AND x IS WIDTH, SO YOU'LL HAVE TO
/// USE COORDINATES AS: object[y][x]
////////////

#pragma once
#include<iostream>

#include"Global_Variables.h"
#include"Map.h"

class Actor
{
public:
	Actor();
	//Actor(Actor&); // "when should i define copy constructor
	Actor(unsigned int y, unsigned int x, int dy, int dx, int movementSpeed, Map* map);

	virtual bool move() = 0;
	virtual void die() = 0;

	void setMovementSpeed(int movementSpeed);
	void setX(unsigned int x, std::ostream& out = std::cout);
	void setY(unsigned int y);
	void setDX(int dx);
	void setDY(int dy);
	void setMap(Map*);

	unsigned int getMovementSpeed() const;
	unsigned int getMovementProgress() const;
	unsigned int getX() const;
	unsigned int getY() const;
	int getDX() const;
	int getDY() const;

	virtual ~Actor(); 
protected:
		bool canMove() const; // decides whether the actor can move with the current x, y, dx and dy
		void executeMoving();
protected:
	static Map* map; // all Actors will use the same map to traverse
private:
	unsigned int x; // how wide
	unsigned int y; // how high

	int dx; // horizontal movement direction, supposed to be either -1, 0 or 1, not decided on it yet tho
	int dy; // vertical movement direction, supposed to be either -1, 0 or 1, not decided on it yet tho

	unsigned int movementSpeed; // lower is faster
	unsigned int movementProgress = 0; // should always be lower than movementSpeed
	//Node* lastVisitedNode; // future implementation
};
