#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>

#define MS_PER_UPDATE 16

int main()
{
	//Creates A Game
	Game game;
	//Game Loop
	auto previous = std::chrono::high_resolution_clock::now();
	double lag = 0.0;
	while (game.isOn())
	{
		auto current = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = current - previous;
		previous = current;
		lag += (elapsed.count() * 1000);
		game.processInput();

		while (lag >= MS_PER_UPDATE)
		{
			game.update();
			lag -= MS_PER_UPDATE;
		}
		
		game.render();
		//comment
	}
}