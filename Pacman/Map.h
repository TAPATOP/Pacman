//////////////////////////////
/// Realises the labyrinth and currently contains the traversing algorithm of A*, e.g. the Bots call it from here.
/// Consists of three levels:
/// -> walkable - whether Actors can traverse it
/// -> logical - used by the AI. For some reason I decided to store if it's a Ghosthouse or not on this level as well
/// -> values - stores each node's value. Keep in mind the default values can be negative
//////////////////////////////

#pragma once
#include<iostream>
#include<cmath>

#include"BotLinkedList.h"
#include"BotStack.h"
#include"Global_Constants.cpp"
#include"mapNode.cpp"

class Map
{
public:
	// not really supposed to be used, placeholder implementation in hopes to avoid an eventual explosion
	Map();

	Map(char** const origMap, unsigned int height, unsigned int width);

	void setWalkable(int y, int x, char changeTo);
	void setValue(int y, int x, int value);
	void setValuableNodesCount(int count);

	unsigned int getMapHeight() const;
	unsigned int getMapWidth() const;
	char getWalkable(int y, int x) const;
	char getLogical(int y, int x) const;
	int getValue(int y, int x) const;
	int getValuableNodesCount() const;
	int getGhostHouseX() const;
	int getGhostHouseY() const;

	unsigned int countNearbyWalkableSquares(int y, int x) const;
	void printMap() const;
	// Says whether the demanded coordinates are valid. I don't think I actually used it
	bool isValidCoord(int y, int x);

	// Finds route from point A to point B using the A* algorithm without using diagonals. Avoids the ghostHouse
	// if necessary
	void buildRouteAstar(int sourceY, int sourceX, int destinationY, int destinationX, BotStack* &commandStack);

	~Map();
private:
	// I don't want anyone copying my Map >:(
	Map(Map&);
	Map& operator=(Map const &);
	
	// Calculates which nodes should be rendered as "knot". Calculated in the constructor
	void processLogicalMap();

	// Calculates the Hcost of all nodes compared to a single point. Can be used for
	// precalculations in the constructor related to the GhostHouse in order to increase efficiency
	void calculateHCost(int y, int x);
private:
	mapNode nodes[gc::maxLoadedMapHeight][gc::maxLoadedMapWidth]; // the map itself
	int valuableNodesCount; // the ammount of nodes that need to be collected before the win condition is met

	unsigned int mapHeight;
	unsigned int mapWidth;

	int ghostHouseCenterX; // where the ghosts go after dying
	int ghostHouseCenterY; // where the ghosts go after dying
};
