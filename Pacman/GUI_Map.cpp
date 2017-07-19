#include "GUI_Map.h"



GUI_Map::GUI_Map()
{
}

GUI_Map::GUI_Map(Map& origMap, sf::Vector2f& vector)
{
	this->map = &origMap;
	
	height = map->getMapHeight();
	width = map->getMapWidth();

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			guiMap[i][j] = new sf::RectangleShape(vector);
			if (map->getWalkable(i, j) == '.')
			{
				guiMap[i][j]->setFillColor(sf::Color::White);
			}
			else if (map->getWalkable(i, j) == '#')
			{
				guiMap[i][j]->setFillColor(sf::Color::Black);
			}
			guiMap[i][j]->setPosition((float)((j + 1) * vector.x), (float)(i * vector.y));
		}
	}
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
