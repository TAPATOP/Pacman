#include "GUI_Map.h"



GUI_Map::GUI_Map()
{
}

GUI_Map::GUI_Map(Map& origMap, sf::Vector2f& squareVector, int yOffset, int xOffset, sf::Texture* allTextures)
{
	this->map = &origMap;
	
	height = map->getMapHeight();
	width = map->getMapWidth();

	this->yOffset = yOffset;
	this->xOffset = xOffset;

	this->allTextures = allTextures;
	textureSizeX = allTextures->getSize().x / 4;
	textureSizeY = allTextures->getSize().y;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			guiMap[i][j] = new sf::RectangleShape(squareVector);
			guiMap[i][j]->setTexture(allTextures);
			if (map->getValue(i, j) == gv::smallBallValue)
			{
				guiMap[i][j]->setTextureRect(sf::IntRect(textureSizeX * 2, 0, textureSizeX, textureSizeY));
			}
			else if (map->getValue(i, j) == gv::bigBallValue)
			{
				guiMap[i][j]->setTextureRect(sf::IntRect(textureSizeX * 3, 0, textureSizeX, textureSizeY));
			}
			else if (map->getWalkable(i, j) == '.')
			{
				guiMap[i][j]->setTextureRect(sf::IntRect(textureSizeX, 0, textureSizeX, textureSizeY));
			}
			else if (map->getWalkable(i, j) == '#')
			{
				guiMap[i][j]->setTextureRect(sf::IntRect(0, 0, textureSizeX, textureSizeY));
			}
			else
			{
				guiMap[i][j]->setTextureRect(sf::IntRect(textureSizeX, 0, textureSizeX, textureSizeY));
			}
			guiMap[i][j]->setPosition((float)(yOffset + j * squareVector.x), (float)(xOffset + i * squareVector.y));
		}
	}
}

void GUI_Map::setRectangleRepresentation(int y, int x, sf::Color color)
{
	guiMap[y][x]->setFillColor(color);
}

void GUI_Map::setRectangleToCollected(int y, int x)
{
	guiMap[y][x]->setTextureRect(sf::IntRect(textureSizeX, 0, textureSizeX, textureSizeY));
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
