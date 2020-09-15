#include "Cutscene_State.h"


//Constructor
Cutscene_State::Cutscene_State(Game_State** current_State, Game_State* next_State)
{
	Cutscene_State::ptr_to_ptr_to_current_State_ = current_State;
	Cutscene_State::next_State_ = next_State;

	//<!> exit() does not work in constructor
}

//Enter and Exit Functions
Game_State* Cutscene_State::enter()
{
	return this;
}

void Cutscene_State::exit()
{
	*ptr_to_ptr_to_current_State_ = next_State_->enter();
}

//GameLoop Functions
void Cutscene_State::processInput(sf::RenderWindow& window)
{
	//SHOULD NOT TAKE ANY INPUTS
}

void Cutscene_State::update(sf::RenderWindow& window, std::vector<Entity*>& eVector)
{
	if (s1.isFinished() == false)
	{
		s1.update();
	}
	else
	{
		s1.reset();
		exit();
	}
}

void Cutscene_State::render(sf::RenderWindow& window, std::vector<Entity*>& eVector)
{
	s1.render(window);
}