#pragma once

class Actor
{
public:
	Actor();

	virtual int move() = 0;
	virtual void die() = 0;

	void setMovementSpeed(float movementSpeed);
	void setX(int x);
	void setY(int y);
	void setDX(int dx);
	void setDY(int dy);

	int getX();
	int getY();
	int getDX();
	int getDY();

	virtual ~Actor();
private:
	int x; // object horizontal location
	int y; // object vertical location

	int dx; // horizontal movement direction, supposed to be either -1, 0 or 1
	int dy; // vertical movement direction, supposed to be either -1, 0 or 1

	float movementSpeed; // lower is faster
	float movementProgress; // should always be lower than movementSpeed

	//Node* lastVisitedNode;
};
