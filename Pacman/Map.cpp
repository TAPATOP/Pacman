#include "Map.h"



Map::Map()
{
	for (unsigned int i = 0; i < 10; i++)
	{
		for (unsigned int j = 0; j < 10; j++)
		{
			nodes[i][j].walkable = gv::walkableSquare;
			nodes[i][j].y = i;
			nodes[i][j].x = j;
		}
	}

	this->mapHeight = 10;
	this->mapWidth = 10;

	valuableNodesCount = 0;
	ghostHouseX = 0;
	ghostHouseY = 0;

	processLogicalMap();
}
// this isnt really supposed to be created, yet
//

Map::Map(char** const origMap, unsigned int mapHeight, unsigned int mapWidth)
{
	if (mapHeight > gv::maxLoadedMapHeight)
	{
		std::cout << "Warning: Given map height higher than allowed! Automatic fix incoming..." << std::endl;
		mapHeight = gv::maxLoadedMapHeight;
	}
	
	if (mapWidth > gv::maxLoadedMapWidth)
	{
		std::cout << "Warning: Given map width higher than allowed! Automatic fix incoming..." << std::endl;
		mapWidth = gv::maxLoadedMapWidth;
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
			if (origMap[i][j] == gv::ghostHouse)
			{
				nodes[i][j].walkable = gv::walkableSquare;
				ghostHouseX = j;
				ghostHouseY = i;
				continue;
			}
			if (origMap[i][j] == gv::smallBall)
			{
				nodes[i][j].value = gv::smallBallValue;
				nodes[i][j].walkable = gv::walkableSquare;
				valuableNodesCount++;
				continue;
			}
			if (origMap[i][j] == gv::bigBall)
			{
				nodes[i][j].value = gv::bigBallValue;
				nodes[i][j].walkable = gv::walkableSquare;
				valuableNodesCount++;
				continue;
			}

			nodes[i][j].value = gv::defaultValue;
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
	return nodes[y][x].knot;
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
	return ghostHouseX;
}
int Map::getGhostHouseY() const
{
	return ghostHouseY;
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

	if (nodes[i][j].walkable == gv::wallSquare) return 0;

	if (i + 1 < (int)mapHeight && nodes[i + 1][j].walkable != gv::wallSquare) br++; // square downwards
	if (i - 1 >= 0 && nodes[i - 1][j].walkable != gv::wallSquare) br++; // square upwards
	if (j - 1 >= 0 && nodes[i][j - 1].walkable != gv::wallSquare) br++; // square to the left
	if (j + 1 < (int)mapWidth && nodes[i][j + 1].walkable != gv::wallSquare) br++; // square to the right

	return br;
}

void Map::printMap() const
{
	//for (unsigned int i = 0; i < mapHeight; i++)
	//{
	//	for (unsigned int j = 0; j < mapWidth; j++)
	//	{
	//		std::cout << (char)nodes[i][j].walkable;
	//	}
	//	std::cout << std::endl;
	//}

	std::cout << std::endl;

	for (unsigned int i = 0; i < mapHeight; i++)
	{
		for (unsigned int j = 0; j < mapWidth; j++)
		{
			std::cout << i << " " << j << " : " << nodes[i][j].y << " " << nodes[i][j].x << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool Map::isValidCoord(int y, int x)
{
	if (!(y >= 0 && y < mapHeight && x >= 0 && x < mapWidth))
	{
		return false;
	}
	return true;
}

void Map::buildRouteAstar(int sourceY, int sourceX, int destinationY, int destinationX, BotStack* &destinationStack)
{
	if (nodes[sourceY][sourceX].walkable == gv::wallSquare)
	{
		std::cout << "The source tile is not walkable??" << std::endl;
		return;
	}

	if (nodes[destinationY][destinationX].walkable == gv::wallSquare)
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
					neighbour->walkable == gv::wallSquare || // if neighbour is not traversible
					closedList.isNodeQueued(neighbour) == 1  // or neighbor is in closedList
					) continue; // proceed to next node

				if (
					(gv::standardMovementCost + current->Gcost ) < neighbour->Gcost || // if new path to neighbor is shorter
					openList.isNodeQueued(neighbour) == 0 // or if neighbor is not in openList
					)
				{
					neighbour->Gcost = current->Gcost + gv::standardMovementCost; // set Fcost
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
	// mapNode* destination = current;
	// 
	// int stackSize = 0;
	// while (current->parent != source)
	// {
	// 	stackSize++;
	// 	current = current->parent;
	// }
	// 
	// current = destination;

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
			if (countNearbyWalkableSquares(i, j) > 2)
			{
				nodes[i][j].knot = gv::knotSquare;
			}
			else
			{
				nodes[i][j].knot = nodes[i][j].walkable;
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
				abs(destinationY - (int)i) * gv::standardMovementCost + abs(destinationX - (int)j) * gv::standardMovementCost;
		}
	}
}
