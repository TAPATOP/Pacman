#pragma once
#include<iostream>

#include"Global_Variables.h"
#include"Map.h"

class Actor
{
public:
	Actor();
	//Actor(Actor&);
	Actor(unsigned int x, unsigned int y, int dx, int dy, float movementSpeed);

	virtual void move() = 0;
	virtual void die() = 0;

	void setMovementSpeed(float movementSpeed);
	void setX(unsigned int x);
	void setY(unsigned int y);
	void setDX(int dx);
	void setDY(int dy);

	float getMovementSpeed() const;
	float getMovementProgress() const;
	unsigned int getX() const;
	unsigned int getY() const;
	int getDX() const;
	int getDY() const;

	virtual ~Actor(); 
protected:
		int canMove() const;
private:
	unsigned int x; // how high
	unsigned int y; // how wide

	int dx; // horizontal movement direction, supposed to be either -1, 0 or 1, not decided on it yet tho
	int dy; // vertical movement direction, supposed to be either -1, 0 or 1, not decided on it yet tho

	float movementSpeed; // lower is faster
	float movementProgress = 0; // should always be lower than movementSpeed

	static Map* map; // all Bots will use the same map to traverse
	//Node* lastVisitedNode; // future implementation
};
