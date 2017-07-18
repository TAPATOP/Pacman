#pragma once

#include"Actor.h"

class Player :
	public Actor
{
public:
	Player();
	Player(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar, int lives,
		char up, char down, char left, char right);

	void setControls(char up, char down, char left, char right);
	void setCurrentCommand(char command);
	void setNextCommand(char command);
	
	unsigned int getScore();
	int getLives();

	sf::Vector2f move();
	void die();
	bool isValidControl(char command);

	~Player();
private:
	void executeCurrentCommand();
	sf::Vector2f interpretCommand(char command);
	void makeNextCommandCurrent();
private:
	unsigned int score;
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
		//char stop;

		char neutral; // e.g. "out of commands"
	};

	Controls controls;
	char currentCommand;
	char nextCommand;
};
