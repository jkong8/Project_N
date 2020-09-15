#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Game_State.h"
#include "Menu_State.h"
#include "Battle_State.h"
#include "Cutscene_State.h"

class Game {
public:
	//Constructor
	Game();

	//Game Loop Functions
	void processInput();
	void update();
	void render();

	//Methods
	bool isOn();
	static bool party[3];
private:
	bool on_;
	//Window
	sf::RenderWindow window_;

	//<!> Apply Entity Vector - IT'S HEAP ALLOCATED
	std::vector<Entity*> eVector;

	//State Pattern
	//Pointer to the current game state
	Game_State* current_State_;
	//Game States
	Menu_State menu_State;
	Battle_State battle_State;
	Cutscene_State cutscene_State;
};