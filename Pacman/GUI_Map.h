#pragma once

#include<SFML/Graphics.hpp>

#include"Map.h"

class GUI_Map
{
public:
	GUI_Map();
	GUI_Map(Map&, sf::Vector2f&, int yOffset, int xOffset);

	void setRectangleRepresentation(int y, int x, sf::Color color);
	void setOffset(int yOffset, int xOffset);

	int getValuableNodesCount();
	int getYOffset();
	int getXOffset();

	void draw(sf::RenderWindow&);

	~GUI_Map();
private:
	Map* map;
	sf::RectangleShape* guiMap[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth];

	int height;
	int width;

	int yOffset = 0;
	int xOffset = 0;
};

