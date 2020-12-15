#pragma once
#include "Game_State.h"
#include "Audio_Manager.h"
class Menu_State : public Game_State
{
public:
	//Constructor
	Menu_State(Game_State**, Game_State*);
	Game_State* enter();
	void exit();
	void processInput(sf::RenderWindow&);
	void update(sf::RenderWindow&, std::vector<Entity*>&);
	void render(sf::RenderWindow&, std::vector<Entity*>&);

	//Struct to draw rain in the main menu
	struct RainDrop
	{
		int width;
		sf::RectangleShape shape;
		sf::Vector2f velocity;
	};
private:
	//Pointer to current_State pointer in Game Class
	Game_State** ptr_to_ptr_to_current_State_;
	//Pointer to the test_State object in the Game Class
	Game_State* next_State_;

	//For Render
	sf::Vertex background_[4];
	RainDrop rain[50];
	sf::Text title_Text_;
	sf::Text play_Text_;
	sf::Text credit_Text_;
	sf::Font font_;
	sf::Vector2f play_Text_Origin_;
	sf::Vector2f credit_Text_Origin_;

	//Audio
	Audio_Manager& a_instance_ = Audio_Manager::getInstance();

	//<!> Delete Later
	Animation sword_animation_;
	Animation bobbn_a2_;
	sf::RectangleShape sword_;
	sf::RectangleShape a2_;
	Animation_Controller sword_anicontroller_;
	Animation_Controller a2_anicontroller_;
};