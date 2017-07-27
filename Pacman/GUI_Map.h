#pragma once

#include<SFML/Graphics.hpp>

#include"Map.h"

class GUI_Map
{
public:
	GUI_Map();
	GUI_Map(Map&, sf::Vector2f&, int yOffset, int xOffset, sf::Texture* allTextures);

	void setRectangleRepresentation(int y, int x, sf::Color color);
	void setRectangleToCollected(int y, int x);
	void setOffset(int yOffset, int xOffset);

	int getValuableNodesCount();
	int getYOffset();
	int getXOffset();

	void draw(sf::RenderWindow&);

	~GUI_Map();
private:
	Map* map;
	sf::RectangleShape* guiMap[gc::maxLoadedMapHeight][gc::maxLoadedMapWidth];

	int height;
	int width;

	int yOffset = 0;
	int xOffset = 0;

	sf::Texture* allTextures;
	int textureSizeX;
	int textureSizeY;
};

