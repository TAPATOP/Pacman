/////////////////////
/// Realizes the player- controlled object(s). Made with the foresight of possible modifications to include multiplayer
/////////////////////
#pragma once

#include"Actor.h"
#include"Bot.h"

class Player :
	public Actor
{
public:
	// shouldn't be used
	Player();
	Player(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar, int lives);
	Player(unsigned int y, unsigned int x, int dy, int dx, unsigned int movementSpeed, Map* map, char displayChar, int lives,
		char up, char down, char left, char right, char stop);

	// Checks if the given command is valid and sets it as current
	void setControls(char up, char down, char left, char right, char stop);
	void setCurrentCommand(char command);

	// Decides whether to dump the current command, if not -> saves a 'nextCommand'
	void setNextCommand(char command);
	
	int getScore() const;
	int getLives() const;

	// / player death
	// Checks for collision and if the player has died due to one sends a message
	// / collects points
	// Collects the current node's points if the player is stationary on it
	// / nextCommand
	// Decides whether to dump the currentCommand and start executing nextCommand
	// 
	ItskoVector2i move();

	// Resets Actors' states and reduces lives
	void die();

	// Checks if given command is saved in the Player's controls
	bool isValidControl(char command);

	~Player();
private:
	// Changes dx and dy to match the command's effect- doesnt move the player, only changes DX and DY
	void executeCurrentCommand();

	// Returns what kind of changes a given command will cause to DX and DY
	ItskoVector2i interpretCommand(char command);
	void makeNextCommandCurrent();
	
	// Ticks currentMovement and handles collisions on the new tile. Chanes Map's walkable accordingly
	ItskoVector2i executeMoving();

	// Checks for collision and returns a value if one is found. Stops at every collision so
	// you have to run it in a loop if you don't want to miss a collision if there are more than one Actors on the field
	int checkCollision();

	// Cycles checkCollision() and returns a value if the player has died
	int handleCollisions();

	void increaseScore(int increase);

	// Collects points from Map's valuable nodes and reduces their counts. Works for any value of empty nodes as well
	void collectValue();
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
