#include "Map.h"



Map::Map()
{
	for (unsigned int i = 0; i < 10; i++)
	{
		for (unsigned int j = 0; j < 10; j++)
		{
			nodes[i][j].walkable = gc::walkableSquare;
			nodes[i][j].y = i;
			nodes[i][j].x = j;
		}
	}

	this->mapHeight = 10;
	this->mapWidth = 10;

	valuableNodesCount = 0;
	ghostHouseCenterX = 0;
	ghostHouseCenterY = 0;

	processLogicalMap();
}
// this isnt really supposed to be created, yet
//

Map::Map(char** const origMap, unsigned int mapHeight, unsigned int mapWidth)
{
	if (mapHeight > gc::maxLoadedMapHeight)
	{
		std::cout << "Warning: Given map height higher than allowed! Automatic fix incoming..." << std::endl;
		mapHeight = gc::maxLoadedMapHeight;
	}
	
	if (mapWidth > gc::maxLoadedMapWidth)
	{
		std::cout << "Warning: Given map width higher than allowed! Automatic fix incoming..." << std::endl;
		mapWidth = gc::maxLoadedMapWidth;
	}
	// Bounds checks
	//

	valuableNodesCount = 0;

	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			nodes[i][j].y = i;
			nodes[i][j].x = j;
			if (origMap[i][j] == gc::ghostHouseCenter)
			{
				nodes[i][j].walkable = gc::walkableSquare;
				nodes[i][j].logical = gc::ghostHouseCenter;
				ghostHouseCenterX = j;
				ghostHouseCenterY = i;
				continue;
			}
			if (origMap[i][j] == gc::ghostHouse)
			{
				nodes[i][j].walkable = gc::walkableSquare;
				nodes[i][j].logical = gc::ghostHouse;
				continue;
			}
			if (origMap[i][j] == gc::smallBall)
			{
				nodes[i][j].value = gc::smallBallValue;
				nodes[i][j].walkable = gc::walkableSquare;
				valuableNodesCount++;
				continue;
			}
			if (origMap[i][j] == gc::bigBall)
			{
				nodes[i][j].value = gc::bigBallValue;
				nodes[i][j].walkable = gc::walkableSquare;
				valuableNodesCount++;
				continue;
			}

			nodes[i][j].value = gc::defaultValue;
			nodes[i][j].walkable = origMap[i][j];
		}
	}
	// copy map
	//

	this->mapHeight = mapHeight;
	this->mapWidth = mapWidth;

	processLogicalMap(); // creates processedMap
}
// CONSTRUCTORS above
//
//

void Map::setWalkable(int y, int x, char changeTo)
{
	nodes[y][x].walkable = changeTo;
}
void Map::setValue(int y, int x, int value)
{
	nodes[y][x].value = value;
}
void Map::setValuableNodesCount(int count)
{
	valuableNodesCount = count;
}
// SETTERS above
//
//

unsigned int Map::getMapHeight() const
{
	return mapHeight;
}

unsigned int Map::getMapWidth() const
{
	return mapWidth;
}

char Map::getWalkable(int y, int x) const
{
	return nodes[y][x].walkable;
}

char Map::getLogical(int y, int x) const
{
	return nodes[y][x].logical;
}
int Map::getValue(int y, int x) const
{
	return nodes[y][x].value;
}
int Map::getValuableNodesCount() const
{
	return valuableNodesCount;
}
int Map::getGhostHouseX() const
{
	return ghostHouseCenterX;
}
int Map::getGhostHouseY() const
{
	return ghostHouseCenterY;
}
// GETTERS above
//
//

unsigned int Map::countNearbyWalkableSquares(int i, int j) const
{
	if (i < 0 || i > (int)mapHeight - 1)
	{
		std::cout << "Error while counting nearby walkable squares for i: " << i << std::endl;
		return 0;
	}

	if (j < 0 || j > (int)mapWidth - 1)
	{
		std::cout << "Error while counting nearby walkable squares for j: " << j << std::endl;
		return 0;
	}

	unsigned int br = 0;

	if (nodes[i][j].walkable == gc::wallSquare) return 0;

	if (i + 1 < (int)mapHeight && nodes[i + 1][j].walkable != gc::wallSquare) br++; // square downwards
	if (i - 1 >= 0 && nodes[i - 1][j].walkable != gc::wallSquare) br++; // square upwards
	if (j - 1 >= 0 && nodes[i][j - 1].walkable != gc::wallSquare) br++; // square to the left
	if (j + 1 < (int)mapWidth && nodes[i][j + 1].walkable != gc::wallSquare) br++; // square to the right

	return br;
}

void Map::printMap() const
{
	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			std::cout << (char)nodes[i][j].walkable;
		}
		std::cout << std::endl;
	}

	//std::cout << std::endl;
	//
	//for (unsigned int i = 0; i < mapHeight; i++)
	//{
	//	for (unsigned int j = 0; j < mapWidth; j++)
	//	{
	//		std::cout << i << " " << j << " : " << nodes[i][j].y << " " << nodes[i][j].x << std::endl;
	//	}
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;
}

bool Map::isValidCoord(int y, int x)
{
	if (!(y >= 0 && y < (int)mapHeight && x >= 0 && x < (int)mapWidth))
	{
		return false;
	}
	return true;
}

void Map::buildRouteAstar(int sourceY, int sourceX, int destinationY, int destinationX, BotStack* &destinationStack)
{
	if (nodes[sourceY][sourceX].walkable == gc::wallSquare)
	{
		std::cout << "The source tile is not walkable??" << std::endl;
		return;
	}

	if (nodes[destinationY][destinationX].walkable == gc::wallSquare)
	{
		std::cout << "DESTINATION TILE NOT WALKABLE ???????????!" << std::endl;
		return;
	}

	//f (sourceX == destinationX && sourceY == destinationY)
	//
	//	std::cout << "You're already at your destination" << std::endl;
	//	return;
	//
	calculateHCost(destinationY, destinationX);

	BotLinkedList openList(&nodes[sourceY][sourceX]);
	BotLinkedList closedList;
	mapNode* current = nullptr;
	mapNode* neighbour;

	while (!openList.isEmpty())
	{
		current = openList.dequeueFirst();
		if (current->x == destinationX && current->y == destinationY)
		{
			break;
		}
		closedList.enqueue(current);

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (!isValidCoord(current->y + i, current->x + j)) continue; // in case it tries to reach nonexistant nodes
				if (abs(i) == abs(j) ) continue; // checks only squares, who share a wall( not a tip) with the current one
				
				neighbour = &nodes[current->y + i][current->x + j];

				if (
					neighbour->walkable == gc::wallSquare || // if neighbour is not traversible
					closedList.isNodeQueued(neighbour) == 1  // or neighbor is in closedList
					) continue; // proceed to next node

				if (
					(gc::standardMovementCost + current->Gcost ) < neighbour->Gcost || // if new path to neighbor is shorter
					openList.isNodeQueued(neighbour) == 0 // or if neighbor is not in openList
					)
				{
					neighbour->Gcost = current->Gcost + gc::standardMovementCost; // set Fcost
					neighbour->parent = current; // set parent of neighbor to current

					if (openList.isNodeQueued(neighbour) == 0) // if neighbour is not in openList
					{
						openList.enqueue(neighbour); // put neighbor in openList
					}
				}
			}
		}

	} 
	// realizes A* algorithm, now we have the address of the target node in current and it's pointing to parents
	//

	if (current == nullptr)
	{
		std::cout << "current in A* is null" << std::endl;
		return;
	}
	mapNode* source = &nodes[sourceY][sourceX];

	if (destinationStack != nullptr) delete destinationStack;

	destinationStack = new BotStack( (current->Gcost) / 10);
	destinationStack->push(current->y, current->x);
	
	while (current->parent != source)
	{
		destinationStack->push(current->parent->y, current->parent->x);
		current = current->parent;
	}
}


Map::~Map()
{
}


void Map::processLogicalMap()
{
	unsigned int i;
	unsigned int j;

	for (i = 0; i < mapHeight; i++)
	{
		for (j = 0; j < mapWidth; j++)
		{
			if (nodes[i][j].logical == gc::ghostHouse || nodes[i][j].logical == gc::ghostHouseCenter)
			{
				continue;
			}
			if (countNearbyWalkableSquares(i, j) > 2)
			{
				nodes[i][j].logical = gc::knotSquare;
			}
			else
			{
				nodes[i][j].logical = nodes[i][j].walkable;
			}
		}
	}
}

void Map::calculateHCost(int destinationY, int destinationX)
{
	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			nodes[i][j].Hcost = 
				abs(destinationY - (int)i) * gc::standardMovementCost + abs(destinationX - (int)j) * gc::standardMovementCost;
		}
	}
}
