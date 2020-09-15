#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Animation_Controller.h"

class Actor
{
public:
	Actor(std::string, sf::Vector2f);
	void update();
	void render(sf::RenderWindow&);

	void reset();
	void say(std::string, int, int, int);
	void moveTo(sf::Vector2f, int, int, int);

	//Test Animation
	Animation_Controller ani_ctrl;
private:
	int speed_;
	bool render_speech_ = false;
	bool moving_ = false;
	sf::RectangleShape rect_;
	sf::Vector2f destination_;
	sf::Vector2f original_position_;
	sf::Vertex speech_box_[4];
	sf::Vertex speech_bg_[4];
	sf::Text text_;
	sf::Text name_;
	sf::Font font_;

	//<!> Delete Later Test Animation
	Animation test_run_animation;
	Animation test_idle_animation;
	void handleMovement_();
};



