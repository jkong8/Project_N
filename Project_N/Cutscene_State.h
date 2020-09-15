#pragma once
#include <SFML/Graphics.hpp>
#include "Game_State.h"
#include "Entity.h"
#include "Actor.h"
#include "Scene.h"

class Cutscene_State : public Game_State
{
public:
	Cutscene_State(Game_State**, Game_State*);
	Game_State* enter();
	void exit();
	void processInput(sf::RenderWindow&);
	void update(sf::RenderWindow&, std::vector<Entity*>&);
	void render(sf::RenderWindow&, std::vector<Entity*>&);

private:
	//Scene Vector to Hold all the cutscene
	//std::vector<Scene> all_scenes_;
	//Pointer to current_State pointer in Game Class
	Game_State** ptr_to_ptr_to_current_State_;
	//Pointer to the test_State object in the Game Class
	Game_State* next_State_;
	
	//Actors

	//Scenes
	Scene_One s1;
};

