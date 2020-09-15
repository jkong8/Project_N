#include "Battle_State.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#define UI_POS_Y 540
#define UI_POS_Y2 710

bool Battle_State::slow_time = false;
Battle_State::Battle_State(Game_State** current_State, Game_State* next_State)
{
	//Assign pointers for state transition
	Battle_State::ptr_to_ptr_to_current_State_ = current_State;
	Battle_State::next_State_ = next_State;
	
	//Initialize members
	select_icon_.setSize(sf::Vector2f(20.0f, 20.0f));
	select_icon_.setFillColor(sf::Color::Red);
	current_party_icon.setSize(sf::Vector2f(20, 20));
	current_party_icon.setFillColor(sf::Color::Cyan);
	select_offset_.x = 40;
	select_offset_.y = -50;

	//Load music
	battle_music_.openFromFile("./Sounds/birth_of_a_wish.wav");

	//Battle UI Stuff <!> On entering battle state, find way to change size of party and enemies
	//battle_ui.create(MAX_PARTY, MAX_ENEMIES); //<-- Change Later
}

Game_State* Battle_State::enter()
{
	initializeParty();
	initializeEnemies();
	battle_ui.create(party_array, party_size_, enemy_size_);
	//battle_music_.play();
	battle_music_.setLoop(true);
	return this;
}

void Battle_State::exit()
{
	//Shows if you lose or win
	std::cout << "Win: " << win << " Lose: " << lose << "\n";
	//Resets win/lose bools
	win = false;
	lose = false;

	//Free up the memory of the enemies array[]
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		delete enemy_array[i];
	}

	//Stop music
	battle_music_.stop();
	//Change State
	*ptr_to_ptr_to_current_State_ = next_State_->enter();
}

void Battle_State::processInput(sf::RenderWindow& window)
{
	sf::Event ev;
	if (window.pollEvent(ev) == true)
	{
		//Mouse Inputs
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			if (!enemy_array[i]->isDead()) {
				if (isHover(window, enemy_array[i]->rectangle()->getPosition(), 100.0f, 150.0f))
				{
					//Move Select Icon
					select_icon_.setPosition(enemy_array[i]->rectangle()->getPosition() + select_offset_);
					show_select_ = true;
					//If you click on enemy. attack them
					if (ev.type == sf::Event::MouseButtonReleased)
					{
						if (battle_ui.command_open == true)
						{
							party_array[active_party_member]->ability_attack(battle_ui.selected_ability, *enemy_array[i]);
							battle_ui.closeCommand();
						}
						else {
							party_array[active_party_member]->basic_attack(*enemy_array[i]);
							//switchBack();
						}
					}
				}
			}
		}

		//Keyboard Input

		if (ev.type == sf::Event::KeyPressed)
		{
			switch (ev.key.code)
			{
				//<!> Think on the issue with switching to party 1 and scrolling
			case sf::Keyboard::S:
				battle_ui.scrollDown();
				battle_ui.openCommand();
				break;
			case sf::Keyboard::W:
				switchPartyMember(1);
				//<!> battle_ui.scrollUp();
				battle_ui.openCommand();
				break;
			case sf::Keyboard::A:
				switchPartyMember(2);
				battle_ui.openCommand();
				break;
			case sf::Keyboard::D:
				switchPartyMember(0);
				battle_ui.openCommand();
				break;
			case sf::Keyboard::C:
				battle_ui.closeCommand();
				switchBack();
			}
		}
	}
}
void Battle_State::update(sf::RenderWindow& window, std::vector<Entity*>& eVector)
{
	controlTimer();
	//Find next available party member
	nextPartyMember();

	if (timer % 10 == 0 || slow_time == false)
	{
		for (int i = 0; i < party_size_; i++)
		{
			party_array[i]->update();
		}

		//Updating enemies
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			if (!enemy_array[i]->isDead())
			{
				enemy_array[i]->update();
				//If the enemy ATP is full, attack a random party member
				if (enemy_array[i]->atpFull())
				{
					//Randomly chooses target
					int target = std::rand() % party_size_;
					//If target is dead, choose a new target
					while (party_array[target]->isDead()) {
						bool allDead = true;
						for (int i = 0; i < party_size_; i++)
						{
							if (!party_array[i]->isDead())
							{
								allDead = false;
								break;
							}
						}
						if (allDead)
						{
							break;
						}

						target = std::rand() % party_size_;
					}
					enemy_array[i]->attack(*party_array[target]);
				}
			}

		}
	}
	

	//Updating UI
	battle_ui.update(enemy_array, party_array, active_party_member);

	//<!> 100% DELETE LATER AND IMPLEMENT BETTER
	current_party_icon.setPosition(party_array[active_party_member]->rectangle()->getPosition() + select_offset_);

	//Check if battle is over
	checkVictory();
	checkDefeat();
}



void Battle_State::render(sf::RenderWindow& window, std::vector<Entity*>& eVector)
{
	//render characters/enemies
	/*aTwo.render(window);
	twoB.render(window);
	nineS.render(window);*/
	for (int i = 0; i < party_size_; i++)
	{
		party_array[i]->render(window);
	}

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemy_array[i]->render(window);
	}

	battle_ui.render(window, active_party_member);
	//render selected icon <!> Move to battle_UI
	if (show_select_)
	{
		window.draw(select_icon_);
	}

	window.draw(current_party_icon);
}

//Initializes the party
void Battle_State::initializeParty()
{
	int index = 0;
	party_size_ = 0;
	for (int i = 0; i < MAX_PARTY; i++)
	{
		if (Game::party[i] == true)
		{
			party_size_++;
			switch (i)
			{
			case 0:
				party_array[index] = &aTwo;
				break;
			case 1:
				party_array[index] = &twoB;
				break;
			case 2:
				party_array[index] = &nineS;
				break;
			}
			index++;
		}
	}

	//Sets position
	for (int i = 0; i < party_size_; i++)
	{
		party_array[i]->rectangle()->setPosition(sf::Vector2f(440 - (200 * i), 195));
	}

	//Resets ATP to 0
	ATwo::s_atp = 0;
	TwoB::s_atp = 0;
	NineS::s_atp = 0;
}

//Initializes the enemy
void Battle_State::initializeEnemies()
{
	enemy_size_ = MAX_ENEMIES;
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemy_array[i] = new Enemy();
		enemy_array[i]->rectangle()->setPosition(sf::Vector2f(740 + (200 * i), 195));
	}
}

void Battle_State::nextPartyMember()
{
	if (party_array[active_party_member]->isAttacking())
	{
		if (switched == true)
		{
			switchBack();
		}
		else if (active_party_member >= party_size_ - 1)
		{
			active_party_member = first_member;
		}
		else
		{
			active_party_member++;
		}
	}
}



void Battle_State::switchPartyMember(int next)
{
	if (next < party_size_)
	{
		switched = true;
		switched_from = active_party_member;
		active_party_member = next;
	}
}

void Battle_State::switchBack()
{
	if (switched == true)
	{
		active_party_member = switched_from;
		switched = false;
	}
}

void Battle_State::controlTimer()
{
	timer++;
	if (timer >= max_timer)
	{
		timer = 0;
	}
	if (timer % 60 == 0)
	{
		std::cout << timer << "\n";
	}
}

void Battle_State::checkVictory()
{
	bool over = true;
	//If an enemy is NOT dead, mark over and lose as false
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (!enemy_array[i]->isDead())
		{
			over = false;
			break;
		}
	}

	//Exits the battle state
	if (over == true)
	{
		win = true;
		Battle_State::exit();
	}
}

void Battle_State::checkDefeat()
{
	bool over = true;
	for (int i = 0; i < party_size_; i++)
	{
		if (!party_array[i]->isDead())
		{
			over = false;
			break;
		}
	}

	//Exits the battle state
	if (over == true)
	{
		lose = true;
		Battle_State::exit();
	}
}
//--------------------------------------Battle_UI--------------------------------------
Battle_State::battle_UI::battle_UI()
{
	font.loadFromFile("./Fonts/slkscr.ttf");

	//COMMAND BOX
	command_text.setFont(font);
	command_text.setCharacterSize(25);
	command_text.setFillColor(sf::Color::Black);
	command_text.setString("Command");

	for (int i = 0; i < 3; i++)
	{
		ability_texts[i].setFont(font);
		ability_texts[i].setCharacterSize(20);
		ability_texts[i].setFillColor(sf::Color::Black);
	}

	//Construct the command box
	Battle_State::battle_UI::command_Box[0] = sf::Vertex(sf::Vector2f(20, 680), sf::Color(255, 255, 158));
	Battle_State::battle_UI::command_Box[1] = sf::Vertex(sf::Vector2f(220, 680), sf::Color(255, 255, 158));
	Battle_State::battle_UI::command_Box[2] = sf::Vertex(sf::Vector2f(220, 710), sf::Color(225, 225, 180));
	Battle_State::battle_UI::command_Box[3] = sf::Vertex(sf::Vector2f(20, 710), sf::Color(225, 225, 180));

	//Party related stuff
	for (int i = 0; i < MAX_PARTY; i++)
	{
		party_names_text[i].setFont(font);
		party_names_text[i].setCharacterSize(25);
		party_names_text[i].setFillColor(sf::Color::Black);

		party_hp_text[i].setFont(font);
		party_hp_text[i].setCharacterSize(25);
		party_hp_text[i].setFillColor(sf::Color::Black);

		party_sp_text[i].setFont(font);
		party_sp_text[i].setCharacterSize(25);
		party_sp_text[i].setFillColor(sf::Color::Black);

		partyATP[i][0].setMaxWidth(200);
		partyATP[i][1].setMaxWidth(200);

		partySP[i].setMaxWidth(250);
	}

	party_names_text[0].setPosition(sf::Vector2f(250, 545));
	party_names_text[1].setPosition(sf::Vector2f(250, 595));
	party_names_text[2].setPosition(sf::Vector2f(250, 645));

	party_hp_text[0].setPosition(sf::Vector2f(725, 545));
	party_hp_text[1].setPosition(sf::Vector2f(725, 595));
	party_hp_text[2].setPosition(sf::Vector2f(725, 645));

	party_sp_text[0].setPosition(sf::Vector2f(1035, 545));
	party_sp_text[1].setPosition(sf::Vector2f(1035, 595));
	party_sp_text[2].setPosition(sf::Vector2f(1035, 645));

	select_icon_box.setSize(sf::Vector2f(35, 25));
	select_icon_box.setFillColor(sf::Color::Black);

	Battle_State::battle_UI::party_Box[0] = sf::Vertex(sf::Vector2f(240, UI_POS_Y), sf::Color(255, 255, 158));
	Battle_State::battle_UI::party_Box[1] = sf::Vertex(sf::Vector2f(1260, UI_POS_Y), sf::Color(255, 255, 158));
	Battle_State::battle_UI::party_Box[2] = sf::Vertex(sf::Vector2f(1260, UI_POS_Y2), sf::Color(255, 255, 158));
	Battle_State::battle_UI::party_Box[3] = sf::Vertex(sf::Vector2f(240, UI_POS_Y2), sf::Color(255, 255, 158));

}

void Battle_State::battle_UI::update(Enemy** enemy_array, Ally** party_array, int active_member)
{
	//Move ability texts to follow command Text
	command_text.setPosition(command_Box[0].position + sf::Vector2f(5, 0));
	ability_texts[0].setPosition(command_text.getPosition() + sf::Vector2f(0, 25));
	ability_texts[1].setPosition(ability_texts[0].getPosition() + sf::Vector2f(0, 25));
	ability_texts[2].setPosition(ability_texts[1].getPosition() + sf::Vector2f(0, 25));
	for (int i = 0; i < 3; i++)
	{
		ability_texts[i].setString(party_array[active_member]->getAbilityName(i));
		ability_texts[i].setFillColor(sf::Color::Black);
	}
	//Highlight ability text
	ability_texts[selected_ability].setFillColor(sf::Color::Blue);
	//Update Command Box
	//Open and close command box
	if (command_open)
	{
		if (command_Box[0].position.y > UI_POS_Y)
		{
			sf::Vector2f rise_speed = sf::Vector2f(0, -10);
			command_Box[0].position = command_Box[0].position + rise_speed;
			command_Box[1].position = command_Box[1].position + rise_speed;
		}
		else
		{
			command_Box[0].position = sf::Vector2f(20, UI_POS_Y);
			command_Box[1].position = sf::Vector2f(220, UI_POS_Y);
		}

		//Ability Texts
		for (int i = 0; i < 3; i++)
		{
		}

	}
	else {
		command_Box[0].position = sf::Vector2f(20, 680);
		command_Box[1].position = sf::Vector2f(220, 680);
	}


	//Update the bars relating to enemy
	for (int i = 0; i < enemy_size; i++)
	{
		//Health Bar
		enemyHP[i].setWidth(150 * (enemy_array[i]->getHp() / enemy_array[i]->getMaxHP()));
		//ATP Bar
		enemyATP[i].setWidth(150 * enemy_array[i]->getAtp() / 1000);
	}

	//Update Party Stuff
	for (int i = 0; i < party_size; i++)
	{
		int hp = party_array[i]->getHp();
		int max_hp = party_array[i]->getMaxHP();
		int sp = party_array[i]->getSP();
		int max_sp = party_array[i]->getMaxSP();
		int atp = party_array[i]->getAtp();

		partyHP[i].setWidth(600 * (party_array[i]->getHp() / party_array[i]->getMaxHP()));
		partyATP[i][0].setWidth(200 * (party_array[i]->getAtp() / 500));
		partyATP[i][1].setWidth(200 * ((party_array[i]->getAtp() - 500) / 500));
		partySP[i].setWidth(250 * (party_array[i]->getSP() / party_array[i]->getMaxSP()));

		std::ostringstream health_text;
		std::ostringstream sp_text;
		health_text << "HP: " << hp << "/" << max_hp;
		sp_text << "SP: " << sp << "/" << max_sp;
		party_hp_text[i].setString(health_text.str());
		party_sp_text[i].setString(sp_text.str());
	}

	//select_icon_box
	select_icon_box.setPosition(party_names_text[active_member].getPosition() + sf::Vector2f(0, 5));
	for (int i = 0; i < MAX_PARTY; i++)
	{
		party_names_text[i].setFillColor(sf::Color::Black);
	}
}

void Battle_State::battle_UI::render(sf::RenderWindow& window, int active_party_member)
{
	//Draw boxes and texts
	window.draw(command_Box, 4, sf::Quads);
	window.draw(party_Box, 4, sf::Quads);
	//window.draw(select_icon_box); <!>
	window.draw(command_text);

	if (command_open) {
		for (int i = 0; i < 3; i++)
		{
			window.draw(ability_texts[i]);
		}
	}

	for (int i = 0; i < party_size; i++)
	{

		window.draw(party_names_text[i]);
		window.draw(party_hp_text[i]);
		window.draw(party_sp_text[i]);

		pHP_bg[i].render(window);
		partyHP[i].render(window);
		partyATP[i][0].render(window);
		partyATP[i][1].render(window);

		pSP_bg[i].render(window);
		partySP[i].render(window);
	}

	//Draw health bars
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemyHP[i].render(window);
		enemyATP[i].render(window);
	}
}


void Battle_State::battle_UI::createEnemyHealthBar()
{
	//Enemy Health Bars
	for (int i = 0; i < enemy_size; i++)
	{
		enemyHP[i].setColor(sf::Color(100, 255, 100), sf::Color(150, 255, 150));
		enemyHP[i].setWidth(0);
		enemyHP[i].createBar(sf::Vector2f(740 + (200 * i), 195), sf::Vector2f(-25, 120));
	}
}

void Battle_State::battle_UI::createEnemyATPBar()
{
	//Enemy ATP Bars
	for (int i = 0; i < enemy_size; i++)
	{
		enemyATP[i].setColor(sf::Color::Blue, sf::Color(150, 150, 255));
		enemyATP[i].setThickness(5);
		enemyATP[i].createBar(sf::Vector2f(740 + (200 * i), 195), sf::Vector2f(-25, 130));
		enemyATP[i].setWidth(0.0f);
	}
}

void Battle_State::battle_UI::createPartyHealthBar()
{
	//Ally Health Bars
	for (int i = 0; i < party_size; i++)
	{
		partyHP[i].setColor(sf::Color::Red, sf::Color::Yellow);
		partyHP[i].createBar(party_names_text[i].getPosition(), sf::Vector2f(50, 30));

		pHP_bg[i].setColor(sf::Color::Black, sf::Color::Black);
		pHP_bg[i].createBar(party_names_text[i].getPosition(), sf::Vector2f(50, 30));
		pHP_bg[i].setWidth(600);
	}
}

void Battle_State::battle_UI::createPartyATPBar()
{
	//Ally ATP Bars
	for (int i = 0; i < party_size; i++)
	{
		partyATP[i][0].setColor(sf::Color::Blue, sf::Color::Black);
		partyATP[i][1].setColor(sf::Color::Blue, sf::Color::Black);
		partyATP[i][0].createBar(party_names_text[i].getPosition(), sf::Vector2f(50, 40));
		partyATP[i][1].createBar(party_names_text[i].getPosition(), sf::Vector2f(275, 40));

	}
}

void Battle_State::battle_UI::createPartySPBar()
{
	for (int i = 0; i < party_size; i++)
	{
		partySP[i].setColor(sf::Color::Cyan, sf::Color::Blue);
		partySP[i].createBar(party_names_text[i].getPosition(), sf::Vector2f(675, 30));
		pSP_bg[i].setColor(sf::Color::Black, sf::Color::Black);
		pSP_bg[i].createBar(party_names_text[i].getPosition(), sf::Vector2f(675, 30));
		pSP_bg[i].setWidth(250);
	}
}

void Battle_State::battle_UI::create(Ally** party_array, int party_size_, int enemy_size_)
{
	party_size = party_size_;
	enemy_size = enemy_size_;
	for (int i = 0; i < party_size_; i++)
	{
		party_names_text[i].setString(party_array[i]->getName());
	}
	createEnemyHealthBar();
	createEnemyATPBar();
	createPartyHealthBar();
	createPartyATPBar();
	createPartySPBar();
}

//Opens Command Box and sets selected ability to 0
void Battle_State::battle_UI::openCommand()
{
	if (command_open == false)
	{
		selected_ability = 0;
		command_open = true;
		Battle_State::slow_time = true;
	}
}

void Battle_State::battle_UI::closeCommand()
{
	command_open = false;
	Battle_State::slow_time = false;
}

void Battle_State::battle_UI::scrollDown()
{
	if (command_open == true)
	{
		if (selected_ability < 2)
		{
			selected_ability++;
		}
		else
		{
			selected_ability = 0;
		}
	}
}

void Battle_State::battle_UI::scrollUp()
{
	if (command_open == true)
	{
		if (selected_ability > 0)
		{
			selected_ability--;
		}
	}
}
void Battle_State::battle_UI::Bar::createBar(sf::Vector2f origin, sf::Vector2f offset)
{
	sf::Vector2f position = origin + offset;
	vertices[0] = sf::Vertex(position, color1);
	vertices[1] = sf::Vertex(position + sf::Vector2f(0, thickness), color1);
	vertices[2] = sf::Vertex(position + sf::Vector2f(width, thickness), color2);
	vertices[3] = sf::Vertex(position + sf::Vector2f(width, 0), color2);
}

void Battle_State::battle_UI::Bar::render(sf::RenderWindow& window)
{
	window.draw(vertices, 4, sf::Quads);
}

void Battle_State::battle_UI::Bar::setWidth(float w)
{
	width = w;
	if (width <= maxWidth) {
		if (width >= 0)
		{
			vertices[2] = sf::Vertex(vertices[0].position + sf::Vector2f(width, thickness), color2);
			vertices[3] = sf::Vertex(vertices[0].position + sf::Vector2f(width, 0), color2);
		}
		else {
			vertices[2] = vertices[0];
			vertices[3] = vertices[1];
		}
	}
}

void Battle_State::battle_UI::Bar::setThickness(int thick)
{
	thickness = thick;
}

float Battle_State::battle_UI::Bar::getWidth()
{
	return width;
}

void Battle_State::battle_UI::Bar::setMaxWidth(float mw)
{
	maxWidth = mw;
}

void Battle_State::battle_UI::Bar::setColor(sf::Color colorOne, sf::Color colorTwo)
{
	color1 = colorOne;
	color2 = colorTwo;
}

bool Battle_State::battle_UI::Bar::isFilled()
{
	if (width == maxWidth)
	{
		return true;
	}
	return false;
}