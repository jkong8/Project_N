#include "Menu_State.h"
#include <iostream>

Menu_State::Menu_State(Game_State** current_State, Game_State* next_State)
{
	//Assign pointers for state transition
	Menu_State::ptr_to_ptr_to_current_State_ = current_State;
	Menu_State::next_State_ = next_State;

	//Load Font
	if (Menu_State::font_.loadFromFile("./Fonts/slkscr.ttf"))
	{
		std::cout << "Font Loaded Success!" << std::endl;
	}

	//Initialize Texts
	Menu_State::title_Text_.setString("Project_N");
	Menu_State::title_Text_.setFont(Menu_State::font_);
	Menu_State::title_Text_.setCharacterSize(60);
	Menu_State::title_Text_.setFillColor(sf::Color::Black);
	Menu_State::title_Text_.setPosition(sf::Vector2f(40,20));
	Menu_State::title_Text_.setStyle(sf::Text::Bold);

	play_Text_Origin_.x = 40;
	play_Text_Origin_.y = 420;
	Menu_State::play_Text_.setString("Play");
	Menu_State::play_Text_.setFont(Menu_State::font_);
	Menu_State::play_Text_.setCharacterSize(45);
	Menu_State::play_Text_.setFillColor(sf::Color::Black);
	Menu_State::play_Text_.setPosition(play_Text_Origin_);

	credit_Text_Origin_.x = 40;
	credit_Text_Origin_.y = 480;
	Menu_State::credit_Text_.setString("Credits");
	Menu_State::credit_Text_.setFont(Menu_State::font_);
	Menu_State::credit_Text_.setCharacterSize(45);
	Menu_State::credit_Text_.setFillColor(sf::Color::Black);
	Menu_State::credit_Text_.setPosition(credit_Text_Origin_);

	//Initialize Background (Custom SFML Shape for gradient background)
	Menu_State::background_[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Color(255,255, 158));
	Menu_State::background_[1] = sf::Vertex(sf::Vector2f(1280, 0), sf::Color(255, 255, 158));
	Menu_State::background_[2] = sf::Vertex(sf::Vector2f(1280, 720), sf::Color(225, 225, 180));
	Menu_State::background_[3] = sf::Vertex(sf::Vector2f(0, 720), sf::Color(225, 225, 180));

	//Initialize RainDrop Array
	for (int i = 0; i < 50; i++)
	{
		int randX = std::rand() % 1280;
		rain[i].width = std::rand() % 3 + 1;
		//Change height base on width
		switch (rain[i].width)
		{
		case 1:
			Menu_State::rain[i].shape.setSize(sf::Vector2f(rain[i].width, 20));
			rain[i].velocity.y = 5;
			break;
		case 2:
			Menu_State::rain[i].shape.setSize(sf::Vector2f(rain[i].width, 30));
			rain[i].velocity.y = 10;
			break;
		case 3:
			Menu_State::rain[i].shape.setSize(sf::Vector2f(rain[i].width, 40));			
			rain[i].velocity.y = 15;
			break;
		
		}
		Menu_State::rain[i].shape.setPosition(sf::Vector2f(randX, 10));
		Menu_State::rain[i].shape.setFillColor(sf::Color::White);
	}

	//Load Audio
	if (Menu_State::main_Music_.openFromFile("./Sounds/city_of_ruin2.wav"))
	{
		std::cout << "Load Music File Success!\n";
		Menu_State::main_Music_.setLoop(true);
	}
	Menu_State::loadSound(Menu_State::ui_Confirmation_, Menu_State::ui_ConfirmationSB_, "./Sounds/ui_confirmation.wav");
	Menu_State::ui_Hover_.setVolume(75);
	Menu_State::loadSound(Menu_State::ui_Hover_, Menu_State::ui_HoverSB_, "./Sounds/ui_hover.wav");
	//Play Music on construction
	Menu_State::main_Music_.play();
}

Game_State* Menu_State::enter()
{
	return this;
}

void Menu_State::exit()
{
	//Stop Audio
	Menu_State::main_Music_.stop();
	//Play Confirmation Audio
	Menu_State::ui_Confirmation_.play();
	//Change State
	*ptr_to_ptr_to_current_State_ = next_State_->enter();
}

void Menu_State::processInput(sf::RenderWindow& window)
{
	//PLAY TEXT
	if (isHover(window, Menu_State::play_Text_Origin_, 200, Menu_State::play_Text_.getLocalBounds().height * 2))
	{
		Menu_State::play_Text_.setPosition(play_Text_Origin_ + sf::Vector2f(100, 0));

		//<!> Figure Out One Shot Method For Audio

		//Clicking Play Text
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			exit();
		}
	}
	else
	{
		Menu_State::play_Text_.setPosition(play_Text_Origin_);
	}

	//CREDIT TEXT
	if (isHover(window, Menu_State::credit_Text_Origin_, 200, Menu_State::credit_Text_.getLocalBounds().height * 2))
	{
		Menu_State::credit_Text_.setPosition(credit_Text_Origin_ + sf::Vector2f(100, 0));
	}
	else
	{
		Menu_State::credit_Text_.setPosition(credit_Text_Origin_);
	}
}

void Menu_State::update(sf::RenderWindow& window, std::vector<Entity*>& eVector)
{
	//Make Rain Drops Fall
	for (int i = 0; i < 50; i++)
	{
		if (rain[i].shape.getPosition().y > 720)
		{
			int randX = std::rand() % 1280;
			rain[i].velocity.y = std::rand() % 5 + 10;
			rain[i].shape.setPosition(randX, 0);
		}
		rain[i].shape.setPosition(rain[i].shape.getPosition() + rain[i].velocity);
	}
	
}

void Menu_State::render(sf::RenderWindow& window, std::vector<Entity*>& eVector)
{

	//Draw Stuff
	window.draw(Menu_State::background_, 4, sf::Quads);
	window.draw(Menu_State::title_Text_);
	window.draw(Menu_State::play_Text_);
	window.draw(Menu_State::credit_Text_);
	//Draw Rain
	for (int i = 0; i < 50; i++)
	{
		window.draw(rain[i].shape);
	}

}

void Menu_State::loadSound(sf::Sound& sound, sf::SoundBuffer& buffer, std::string filepath)
{
	if (buffer.loadFromFile(filepath))
	{
		std::cout << "Load Sound File Success!\n";
		sound.setBuffer(buffer);
	}
}