////////////
/// PLEASE NOTE THAT y IS HEIGHT AND x IS WIDTH, SO YOU'LL HAVE TO
/// USE COORDINATES AS: object[y][x]
////////////

////
/// Class used to simulate the common qualities and capabilities of Player and Bots
////

#pragma once
#include<iostream>

#include"Global_Constants.cpp"
#include"ItskoVector2i.h"
#include"Map.h"

class Actor
{
public:
	// default constructor, shouldnt be used
	Actor();
	Actor(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar);
	Actor(unsigned int y, unsigned int x, unsigned int startingY, unsigned int startingX, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar);

	void setMovementSpeed(unsigned int movementSpeed);
	void setMovementProgress(int movementProgress);
	void setX(unsigned int x);
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

	// pure virtual function
	virtual ItskoVector2i move() = 0;
	// pure virtual function
	virtual void die() = 0;
	// pure virtual function, sends the Actor back to his startingX and startingY and sets movementProgress to 0
	virtual void resetPosition();

	virtual ~Actor(); 
protected:
		// uses canMove(ItskoVector2i&) by passing the current DX and DY automatically as an ItskoVector2i
		bool canMove() const;

		// / coord validation
		// Checks if the future coordinates are valid(e.g. part of the map)
		// / check for wall
		// Checks if the future tile is a wall;
		// / house handling  
		// If the future tile is a house -> if the current one isnt a house as well, then the actor cannot move in that direction
		bool canMove(ItskoVector2i& newDirections) const;

		// / movementProgress tick
		// Ticks movement progress once and then checks if it has reached the movementSpeed
		// / map change
		// If the target speed is reached, changes the map's walkable squares -> the one the actor is currently on is made 'walkable'
		// and the node the Actor has moved to is changed to the Actor's displayChar
		virtual ItskoVector2i executeMoving();
protected:
	Map* map; // all Actors will use the same map to traverse
private:
	unsigned int x; // row of map
	unsigned int y; // column of map
	
	unsigned int startingX; // used when the player dies and the actors' positions are reset, = x by default
	unsigned int startingY; // used when the player dies and the actors' positions are reset, = y by default

	int dx; // horizontal movement direction, supposed to be either -1, 0 or 1, not decided on it yet tho
	int dy; // vertical movement direction, supposed to be either -1, 0 or 1, not decided on it yet tho

	int movementSpeed; // lower is faster
	int movementProgress = 0; // should always be lower than movementSpeed

	char displayChar; // used to display the character on the map's walkable hash
protected:
	static const unsigned int maxActors = 10; // maximum ammount of registrable Actors
	static Actor* allActors[maxActors]; // an array registering all of the Actors
	static int allActorsCount; // the ammount of registered Actors
};
