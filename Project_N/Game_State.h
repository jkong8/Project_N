#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>>
#include "Entity.h"

#define MAX_ENEMIES 3
#define MAX_PARTY 3 //For now

//Base Class that handles all the game states
class Game_State
{
public:
	virtual Game_State* enter() = 0;
	virtual void exit() = 0;
	virtual void processInput(sf::RenderWindow&) = 0;
	virtual void update(sf::RenderWindow&, std::vector<Entity*>&) = 0;
	virtual void render(sf::RenderWindow&, std::vector<Entity*>&) = 0;
	//Check if mouse hover over a location
	bool isHover(sf::RenderWindow&, sf::Vector2f, float, float);
private:
	
};