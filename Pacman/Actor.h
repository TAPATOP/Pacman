////////////
/// PLEASE NOTE THAT y IS HEIGHT AND x IS WIDTH, SO YOU'LL HAVE TO
/// USE COORDINATES AS: object[y][x]
////////////

#pragma once
#include<iostream>
#include<SFML/Graphics/Vertex.hpp>

#include"Global_Variables.h"
#include"Map.h"

class Actor
{
public:
	Actor();
	//Actor(Actor&); // "when should i define copy constructor"
	Actor(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar);

	void setMovementSpeed(unsigned int movementSpeed);
	void setMovementProgress(unsigned int movementProgress);
	void setX(unsigned int x, std::ostream& out = std::cout);
	void setY(unsigned int y);
	void setDX(int dx);
	void setDY(int dy);
	void setMap(Map*);

	unsigned int getMovementSpeed() const;
	unsigned int getMovementProgress() const;
	int getX() const;
	int getY() const;
	int getDX() const;
	int getDY() const;

	virtual sf::Vector2f move() = 0;
	virtual void die() = 0;

	virtual ~Actor(); 
protected:
		bool canMove() const;
		bool canMove(sf::Vector2f newDirections) const;// decides whether the actor can move with the current x, y, dx and dy
		sf::Vector2f executeMoving(); // moves the actor according to x, y, dx, dy and his speed
protected:
	Map* map; // all Actors will use the same map to traverse
private:
	unsigned int x; // how wide
	unsigned int y; // how high

	int dx; // horizontal movement direction, supposed to be either -1, 0 or 1, not decided on it yet tho
	int dy; // vertical movement direction, supposed to be either -1, 0 or 1, not decided on it yet tho

	unsigned int movementSpeed; // lower is faster
	unsigned int movementProgress = 0; // should always be lower than movementSpeed

	char displayChar;
	//Node* lastVisitedNode; // future implementation
public:
	static const unsigned int maxActors = 10;
	static Actor* allActors[maxActors];
	static int allActorsCount;
};
