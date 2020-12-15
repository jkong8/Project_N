#include "Game.h"
#include <iostream>
#define WIDTH 1280
#define HEIGHT 720

bool Game::party[3] = { true, true, true };
//Constructor
Game::Game() :
	menu_State(&current_State_, &cutscene_State),
	battle_State(&current_State_, &menu_State),
	cutscene_State(&current_State_, &battle_State)
{
	//Set on_ to true
	Game::on_ = true;
	//Create a window on Game initialization
	Game::window_.create(sf::VideoMode(WIDTH, HEIGHT), "Project N");	
	Game::window_.setFramerateLimit(60);
	//<!> Set the game state - NOT STATIC
	Game::current_State_ = menu_State.enter();
	//<!> DELETE LATER Adding a Entity to the vector to test
	eVector.push_back(new TwoB());
}
//Game Loops Functions
//Process Input - <!> IS THIS A USELESS METHOD
void Game::processInput()
{
	Game::current_State_->processInput(window_);
}

//Update
void Game::update()
{
	Game::current_State_->update(Game::window_, Game::eVector);
}

//Render
void Game::render()
{
	sf::Event event;
	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window_.close();
			Game::on_ = false;
		}
	}
	//Clear Window
	window_.clear(sf::Color(0, 0, 0));

	Game::current_State_->render(Game::window_, Game::eVector);

	//Display
	window_.display();
}

//Methods
bool Game::isOn()
{
	return Game::on_;
}


