#include "Actor.h"
#include <iostream>
#define UI_POS_Y 540
#define UI_POS_Y2 710

Actor::Actor(std::string name, sf::Vector2f original_position) :
	test_run_animation(rect_, "./Textures/run-sheet.png"),
	test_idle_animation(rect_, "./Textures/idle_sheet.png")
{
	//Initialize Rect
	original_position_ = original_position;
	rect_.setSize(sf::Vector2f(100, 100));
	rect_.setPosition(original_position_);

	//Initialize Text and Font
	font_.loadFromFile("./Fonts/slkscr.ttf");
	text_.setFont(font_);
	text_.setCharacterSize(25);
	text_.setFillColor(sf::Color::Black);
	text_.setPosition(sf::Vector2f(30, UI_POS_Y + 40));
	
	name_.setFont(font_);
	name_.setCharacterSize(25);
	name_.setFillColor(sf::Color::Black);
	name_.setString(name);
	name_.setPosition(sf::Vector2f(30, UI_POS_Y + 10));

	//Initialize Speech Box 
	speech_box_[0] = sf::Vertex(sf::Vector2f(20, UI_POS_Y), sf::Color(255, 255, 158));
	speech_box_[1] = sf::Vertex(sf::Vector2f(1260, UI_POS_Y), sf::Color(255, 255, 158));
	speech_box_[2] = sf::Vertex(sf::Vector2f(1260, UI_POS_Y2), sf::Color(255, 255, 158));
	speech_box_[3] = sf::Vertex(sf::Vector2f(20, UI_POS_Y2), sf::Color(255, 255, 158));

	//Speech Background 5px border
	speech_bg_[0] = sf::Vertex(sf::Vector2f(15, UI_POS_Y - 5), sf::Color::Black);
	speech_bg_[1] = sf::Vertex(sf::Vector2f(1265, UI_POS_Y - 5), sf::Color::Black);
	speech_bg_[2] = sf::Vertex(sf::Vector2f(1265, UI_POS_Y2 + 5), sf::Color::Black);
	speech_bg_[3] = sf::Vertex(sf::Vector2f(15, UI_POS_Y2 + 5), sf::Color::Black);

	//Initialize Animations
	test_run_animation.setParameters(100, 74, 1, 6, 6);
	test_idle_animation.setParameters(100, 74, 1, 4, 10);
	ani_ctrl.addAnimation(test_run_animation);
	ani_ctrl.addAnimation(test_idle_animation);
	ani_ctrl.loop(1);
}

void Actor::update()
{
	ani_ctrl.animate();
	handleMovement_();
	//<!> Delete Later
}

void Actor::render(sf::RenderWindow& window)
{
	//Renders Rectangle
	window.draw(rect_);

	//Rectangles Speech
	if (render_speech_ == true)
	{
		window.draw(speech_bg_, 4, sf::Quads);
		window.draw(speech_box_, 4, sf::Quads);
		window.draw(text_);
		window.draw(name_);
	}
}

void Actor::reset()
{
	rect_.setPosition(original_position_);
	moving_ = false;
	render_speech_ = false;
}

void Actor::say(std::string text, int starting_time, int duration, int timer)
{
	if (timer == starting_time)
	{
		render_speech_ = true;
		text_.setString(text);
	}

	if (timer == starting_time + duration)
	{
		render_speech_ = false;
	}
}

void Actor::moveTo(sf::Vector2f destination, int speed, int starting_time, int timer)
{
	if (timer == starting_time)
	{
		ani_ctrl.loop(0);
		destination_ = destination;
		speed_ = speed;
		moving_ = true;
	}
}

void Actor::handleMovement_()
{
	if (moving_ == true) 
	{
		//Velocity Might not work
		if (rect_.getPosition().x != destination_.x || rect_.getPosition().y != destination_.y)
		{

			if (rect_.getPosition().x < destination_.x)
			{
				rect_.setPosition(rect_.getPosition() + sf::Vector2f(speed_, 0));
			}
			else if(rect_.getPosition().x > destination_.x)
			{
				rect_.setPosition(rect_.getPosition() + sf::Vector2f(-speed_, 0));
			}

			if (rect_.getPosition().y < destination_.y)
			{
				rect_.setPosition(rect_.getPosition() + sf::Vector2f(0, speed_));
			}
			else if (rect_.getPosition().y > destination_.y)
			{
				rect_.setPosition(rect_.getPosition() + sf::Vector2f(0, -speed_));
			}
		}
		else 
		{
			moving_ == false;
			ani_ctrl.loop(1);
		}
	}
}

