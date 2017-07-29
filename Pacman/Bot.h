/////////////////////
/// Realises all of the AI and non- player controlled behaviours
/////////////////////

#pragma once
#include <cstdlib>
#include <ctime>

#include"Actor.h"
#include"BotStack.h"

class Bot :
	public Actor
{
public:
	// should not be used
	Bot();
	Bot(int botID, unsigned int y, unsigned int x, int dy, int dx, int dedicatedY, int dedicatedX, unsigned int movementSpeed, Map* map, char displayChar);

	// sets isVulnerable, raises the checkMe flag and resets the vulnerabilityTimer
	// #if is now Vulnerable, deletes the commandStack, so vulnerableBehaviour can do it's work
	void setIsVulnerable(bool);

	// sets isGhost, sets isVulnerable to 0, raises the checkMe flag and deletes the commandStack
	// # if the actor is now a Ghost, deletes the commandStack, so ghostBehaviour can do it's work
	// # else sets DX and DY to 0 and sends the Bot back to patrol to it's dedicated node after it dies
	void setIsGhost(bool);
	void setID(int);
	void setCheckMe(bool);

	bool getIsVulnerable() const;
	bool getIsGhost() const;
	int getID() const;
	bool getCheckMe() const;
	int getVulnerabilityTimer() const;

	// Does everything related to moving -> from ticking, to changing behaviour, to executing commandStack
	// / vulnerabilityTimer
	// Ticks the vulnerabilityTimer 
	// # if it reaches it's limit, isVulnerable(0) and calls emergencyExecute()
	// # else vulnerableBehaviour()
	// / Handles non-existant commandStack, executes the commandStack, checks if Bot has reached ghostHouseCenter
	// # if the stack is non-existant
	// ## if isGhost -> ghostBehaviour()
	// ## else executes allocated to Bot behaviour
	// # else 
	// ## if the Bot hasnt started moving yet and the commandStack isEmpty()
	// Executes the top of the stack and returns
	// ## if the Bot is in the ghostHouse -> setIsGhost(0)
	// ## if the bot hasn't started moving and commandStack is empty
	// returns emergencyExecute()
	ItskoVector2i move();

	// sets flags and executes ghostBehaviour
	void die();

	void deleteStack();

	~Bot();
private:
	// Picks random DX and DY, making sure they're not the opposite of the previous ones, unless
	// explicitly told not to make that check by giving a boolean value mustBeOppositeToOldDXDY = 0
	void pickRandomDirection(bool mustBeOppositeToOldDXDY = 1);

	// Adjusts DX and DY in such way so the bot will traverse it properly
	void cornerSolver();

	// Reverses DX and DY, so the bot moves backwards
	void reverseDirection();

	// Resets position and sends bot to dedicated node
	void resetPosition();

	// Fills the stack with commands to the dedicated point by using findRouteToDestination() 
	void findRouteToDedicatedPoint();

	// Pointer to function, is only set in the constructor based on botID
	void (Bot::*botBehaviour)();

	// Pretty much random movement
	void defaultBehaviour();

	// Finds the Player and uses findRouteToDestination to trace the Player. Only updates when all of the commands are executed
	void seekingBehaviour();

	// Fills the commandStack with coordinates of the route back to the ghostHouseCenter
	void ghostBehaviour();

	// Currently uses the defaultBehaviour
	void vulnerableBehaviour();

	// / deletes commandStack
	// Deletes the commandStack and fills it up with the allocated Behaviour. If the commandStack is still empty,
	// executes the defaultBehaviour. Returns executeMoving()
	ItskoVector2i emergencyExecute();

	// Finds route to destination using A* without diagonal movement
	void findRouteToDestination(int destinationY, int destinationX);

private:
	bool isVulnerable = 0; // if true, then the Player can kill the Bot
	bool isGhost = 0; // if true, then it's moving back to the house and cannot interact with the Player

	bool checkMe = 0; // used to tell the GUI when to check for change of display Texture

	int vulnerabilityTimer = 0; // compared with VTimer, when it exceeds it -> Bot is no longer Vulnerable

	int botID; // I want it manually set for now

	BotStack* commandStack = nullptr; // algorithms push coordinates of nodes here and then the Bot follows them
	int dedicatedX = 0; // coordinates of the point bot goes to by default(similar to original Pacman's Scatter mode)
	int dedicatedY = 0; // coordinates of the point bot goes to by default(similar to original Pacman's Scatter mode)
};
