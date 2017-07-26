#include "GUI_Map.h"



GUI_Map::GUI_Map()
{
}

GUI_Map::GUI_Map(Map& origMap, sf::Vector2f& squareVector, int yOffset, int xOffset)
{
	this->map = &origMap;
	
	height = map->getMapHeight();
	width = map->getMapWidth();

	this->yOffset = yOffset;
	this->xOffset = xOffset;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			guiMap[i][j] = new sf::RectangleShape(squareVector);
			if (map->getValue(i, j) == gv::smallBallValue)
			{
				guiMap[i][j]->setFillColor(sf::Color::Yellow);
			}
			else if (map->getValue(i, j) == gv::bigBallValue)
			{
				guiMap[i][j]->setFillColor(sf::Color::Color(100, 150, 10, 255));
			}
			else if (map->getWalkable(i, j) == '.')
			{
				guiMap[i][j]->setFillColor(sf::Color::White);
			}
			else if (map->getWalkable(i, j) == '#')
			{
				guiMap[i][j]->setFillColor(sf::Color::Black);
			}
			guiMap[i][j]->setPosition((float)(yOffset + j * squareVector.x), (float)(xOffset + i * squareVector.y));
		}
	}
}

void GUI_Map::setRectangleRepresentation(int y, int x, sf::Color color)
{
	guiMap[y][x]->setFillColor(color);
}

void GUI_Map::setOffset(int yOffset, int xOffset)
{
	this->yOffset = yOffset;
	this->xOffset = xOffset;
}

int GUI_Map::getValuableNodesCount()
{
	return map->getValuableNodesCount();
}

int GUI_Map::getYOffset()
{
	return yOffset;
}

int GUI_Map::getXOffset()
{
	return xOffset;
}

void GUI_Map::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			window.draw(*guiMap[i][j]);
		}
	}
}


GUI_Map::~GUI_Map()
{
}
