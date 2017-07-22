#pragma once

#include"Actor.h"
#include"Bot.h"

class Player :
	public Actor
{
public:
	Player();
	Player(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar, int lives);
	Player(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar, int lives,
		char up, char down, char left, char right, char stop);

	void setControls(char up, char down, char left, char right);
	void setCurrentCommand(char command);
	void setNextCommand(char command);
	
	int getScore();
	int getLives();

	ItskoVector2i move();
	void die();
	bool isValidControl(char command);

	~Player();
private:
	void executeCurrentCommand();
	ItskoVector2i interpretCommand(char command);
	void makeNextCommandCurrent();
	
	ItskoVector2i executeMoving();
	int checkCollision();
private:
	int score;
	int lives;
	
	///////////////////
	/// Controls below
	///////////////////

	struct Controls
	{
		char up;
		char down;
		char left;
		char right;
		char stop;

		char neutral; // e.g. "out of commands"
	};

	Controls controls;
	char currentCommand;
	char nextCommand;
};
