#pragma once

#include<SFML/Graphics.hpp>

#include"Map.h"

class GUI_Map
{
public:
	GUI_Map();
	GUI_Map(Map&, sf::Vector2f&);

	void draw(sf::RenderWindow&);

	~GUI_Map();
private:
	Map* map;
	sf::RectangleShape* guiMap[gv::maxLoadedMapHeight][gv::maxLoadedMapWidth];

	int height;
	int width;
};

