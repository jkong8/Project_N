#include "Game_State.h"
#include <iostream>

bool Game_State::isHover(sf::RenderWindow& window, sf::Vector2f origin, float width, float height)
{
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;

	if (mouseX >= origin.x && mouseX <= origin.x + width &&
		mouseY >= origin.y && mouseY <= origin.y + height)
	{
		return true;
	}

	return false;
}