#include "Entity.h"
#include <iostream>
//----------------------Base Class----------------------
Entity::Entity() : x_(0), y_(0) 
{
	Entity::rectangle_.setPosition(sf::Vector2f(*x(), *y()));
	Entity::rectangle_.setSize(sf::Vector2f(55.0f, 150.0f));
}


float* Entity::x() { return &x_; }
float* Entity::y() { return &y_; }
float Entity::getHp() { return health_; }
float Entity::getAtp() { return atp_; }
float Entity::getAttack() { return attack_; }
float Entity::getDefense() { return defense_; }
float Entity::getMaxHP() { return maxHp_; }
float Entity::getMaxATP() { return MAX_ATP; };
void Entity::setHp(float hp) { health_ = hp; }
void Entity::setAtp(float atp) { atp_ = atp; }
void Entity::setAttack(float attack) { attack_ = attack; }
void Entity::setDefense(float defense) { defense_ = defense; }
void Entity::setMaxHP(float mhp) { maxHp_ = mhp; }

bool Entity::atpFull()
{
	if (getAtp() >= getMaxATP())
	{
		return true;
	}
	return false;
}
bool Entity::isDead() 
{ 
	if (health_ <= 0)
	{
		setAtp(0);
		setHp(0);
		return true;
	}

	return false;
}
void Entity::setPosition(float x, float y)
{
	Entity::x_ = x;
	Entity::y_ = y;
	Entity::rectangle()->setPosition(x_, y_);
}

sf::RectangleShape* Entity::rectangle()
{
	return &rectangle_;
}

//----------------------Ally Class----------------------

bool Ally::isAttacking() { return attacking_; }
void Ally::setAttacking(bool attack) { attacking_ = attack; }
void Ally::setDelay(int delay) { delay_ = delay; }
void Ally::handleDelay()
{
	if (delay_ <= 0)
	{
		attacking_ = false;
	}
	else
	{
		delay_--;
	}
}

//----------------------A2 Class----------------------
float ATwo::s_max_health = 250;
float ATwo::s_health = ATwo::s_max_health;
float ATwo::s_atp = 0;
float ATwo::s_max_sp = 30;
float ATwo::s_sp = ATwo::s_max_sp;

const std::string ATwo::s_name = "A2";
const std::string ATwo::s_ability_names[3] = { "A2 Ability One", "A2 Ability Two", "A2 Ability Three" };

ATwo::ATwo() :
	//Creating the animation in constructor list
	test_Animation_(*ATwo::rectangle(), "./Textures/attack-sheet.png"),
	head_bobbn_(*ATwo::rectangle(), "./Textures/A2_Bobbn_Idle.png"),
	battle_idle_(*ATwo::rectangle(), "./Textures/A2_Battle_Idle.png")
{
	//Adds the animations to the animation controller
	animation_Controller_.addAnimation(battle_idle_);		//0 - DEFAULT
	animation_Controller_.addAnimation(test_Animation_);	//1
	animation_Controller_.addAnimation(head_bobbn_);		//2
	
	//Sets parameters for all animations
	animation_Controller_.getAnimation(0).setParameters(55, 150, 1, 4, 30);
	animation_Controller_.getAnimation(1).setParameters(100, 74, 2, 7, 4);
	animation_Controller_.getAnimation(2).setParameters(55, 150, 1, 4, 30);
	//Sets the stats 
	setAttack(10);
	setDefense(10);
	setMaxHP(250);
	setHp(getMaxHP());
	//Loops first animation
	animation_Controller_.loopDefault(true);
}

void ATwo::update()
{
	//<!> Changes color when attacking - DELETE LATER
	if (isAttacking())
	{
		rectangle()->setFillColor(sf::Color::Blue);
	}
	else {
		rectangle()->setFillColor(sf::Color::White);
	}
	//Handles ATP
	if (s_atp <= MAX_ATP) {
		s_atp++;
	}
	//isDead
	isDead();
	ATwo::animation_Controller_.animate();
	ATwo::handleDelay();
}

void ATwo::render(sf::RenderWindow& window)
{
	window.draw(*ATwo::rectangle());
}

void ATwo::takeDamage(float damage)
{
	ATwo::s_health -= damage;
}

std::string ATwo::getAbilityName(int index)
{
	return ATwo::s_ability_names[index];
}

std::string ATwo::getName()
{
	return ATwo::s_name;
}

void ATwo::ability_attack(int attack, Entity& target)
{
	switch (attack)
	{
	case 0:
		ability_one(target);
		break;
	case 1:
		ability_two(target);
		break;
	case 2:
		ability_three(target);
		break;
	default:
		basic_attack(target);
	}
}

void ATwo::basic_attack(Entity& target)
{
	if (!isAttacking())
	{
		//Play Audio
		a_instance.basic_damage_.play();
		//Do damage calculations
		target.setHp(target.getHp() - getAttack());
		setAttacking(true);
		animation_Controller_.start(1);
		setDelay(60);
		std::cout << "BASIC ATTACK\n";
	}
}

void ATwo::ability_one(Entity& target)
{
	if (!isAttacking() && hasSP_(5)  && hasATP_() )
	{
		target.setHp(target.getHp() - (getAttack() + 20));
		ATwo::s_sp -= 5;
		setAttacking(true);
		animation_Controller_.start(1);
		setDelay(100);
		std::cout << "Ability One\n";
	}
}

void ATwo::ability_two(Entity& target)
{
	if (!isAttacking() && hasSP_(10) && hasATP_() )
	{
		target.setHp(target.getHp() - (getAttack() + 50));
		ATwo::s_sp -= 10;
		setAttacking(true);
		animation_Controller_.start(1);
		setDelay(180);
		std::cout << "Ability Two\n";
	}
}

void ATwo::ability_three(Entity& target)
{
	if (!isAttacking() && hasSP_(15)  && hasATP_() )
	{
		target.setHp(target.getHp() - (getAttack() + 70));
		ATwo::s_sp -= 15;
		setAttacking(true);
		animation_Controller_.start(1);
		setDelay(300);
		std::cout << "Ability Three\n";
	}
}

bool ATwo::isDead()
{
	if (ATwo::s_health <= 0)
	{
		std::cout << "A2 IS DEAD\n";
		s_health = 0;
		return true;
	}
	return false;
}

float ATwo::getHp()
{
	return ATwo::s_health;
}

float ATwo::getAtp()
{
	return ATwo::s_atp;
}

float ATwo::getMaxHP()
{
	return ATwo::s_max_health;
}

float ATwo::getSP()
{
	return ATwo::s_sp;
}

float ATwo::getMaxSP()
{
	return ATwo::s_max_sp;
}

bool ATwo::hasSP_(float cost)
{
	if ((ATwo::s_sp - cost < 0))
	{
		return false;
	}
	else 
	{
		return true;
	}
}

bool ATwo::hasATP_()
{
	if ((ATwo::s_atp - 500 < 0))
	{
		return false;
	}
	else 
	{
		ATwo::s_atp -= 500;
		return true;
	}
}




//----------------------TwoB Class----------------------
float TwoB::s_max_health = 200;
float TwoB::s_health = TwoB::s_max_health;
float TwoB::s_atp = 0;
float TwoB::s_max_sp = 30;
float TwoB::s_sp = TwoB::s_max_sp;
const std::string TwoB::s_ability_names[3] = { "2B Ability One", "2B Ability Two", "2B Ability Three" };
const std::string TwoB::s_name = "2B";

TwoB::TwoB() :
	//<!> TEST ANIMATIONS
	test_Animation_(*TwoB::rectangle(), "./Textures/attack-sheet.png"),
	battle_idle_(*TwoB::rectangle(), "./Textures/2B_Battle_Idle.png")
{
	//Adding Animations to Controller
	animation_Controller_.addAnimation(battle_idle_);
	animation_Controller_.addAnimation(test_Animation_);
	animation_Controller_.getAnimation(0).setParameters(55, 150, 1, 4, 30); //0
	animation_Controller_.getAnimation(1).setParameters(100, 74, 2, 7, 4);	//1

	//Setting Stats
	setAttack(10);
	setDefense(10);
	setMaxHP(250);
	setHp(getMaxHP());

	//Loop Default (0) animation
	animation_Controller_.loopDefault(true);
}

void TwoB::update()
{
	//<!> Changes color when attacking - DELETE LATER
	if (isAttacking())
	{
		rectangle()->setFillColor(sf::Color::Blue);
	}
	else {
		rectangle()->setFillColor(sf::Color::White);
	}
	//Increment ATP <!> Delete Later
	if (s_atp <= MAX_ATP) {
		s_atp++;
	}
	//isDead
	isDead();
	//Testing HP in UI <!> Delete Later
	TwoB::animation_Controller_.animate();
	TwoB::handleDelay();
}

void TwoB::render(sf::RenderWindow& window)
{
	window.draw(*TwoB::rectangle());
}

void TwoB::takeDamage(float damage)
{
	TwoB::s_health -= damage;
}

std::string TwoB::getAbilityName(int index)
{
	return TwoB::s_ability_names[index];
}

std::string TwoB::getName()
{
	return TwoB::s_name;
}

void TwoB::ability_attack(int attack, Entity& target)
{
	switch (attack)
	{
	case 0:
		ability_one(target);
		break;
	case 1:
		ability_two(target);
		break;
	case 2:
		ability_three(target);
		break;
	default:
		basic_attack(target);
	}
}

//Attacks and Abilities
//All attacks should do some changes to target or self, play animation, add a delay timer
void TwoB::basic_attack(Entity& target)
{
	if (!isAttacking())
	{
		//Play Audio
		a_instance.basic_damage_.play();
		//Do damage calculations
		target.setHp(target.getHp() - getAttack());
		setAttacking(true);
		animation_Controller_.start(1);
		setDelay(60);//delay actions by 60 frames
		std::cout << "BASIC ATTACK\n";
	}
}

//+20 DMG
void TwoB::ability_one(Entity& target)
{
	if (!isAttacking() && hasSP_(5) && hasATP_() )
	{
		target.setHp(target.getHp() - (getAttack() + 20));
		TwoB::s_sp -= 5;
		setAttacking(true);
		animation_Controller_.start(1);
		setDelay(100);//delay actions by 60 frames
		std::cout << "Ability One\n";
	}
}

//+50 DMG
void TwoB::ability_two(Entity& target)
{
	if (!isAttacking() && hasSP_(10) && hasATP_() )
	{
		target.setHp(target.getHp() - (getAttack() + 50));
		TwoB::s_sp -= 10;
		setAttacking(true);
		animation_Controller_.start(1);
		setDelay(180);//delay actions by 180 frames
		std::cout << "Ability Two\n";
	}
}
 //+70
void TwoB::ability_three(Entity& target)
{
	if (!isAttacking() && hasSP_(15) && hasATP_() )
	{
		target.setHp(target.getHp() - (getAttack() + 70));
		TwoB::s_sp -= 15;
		setAttacking(true);
		animation_Controller_.start(1);
		setDelay(300);//delay actions by 300 frames
		std::cout << "Ability Three\n";
	}
}

bool TwoB::isDead()
{
	if (TwoB::s_health <= 0)
	{
		std::cout << "2B IS DEAD\n";
		TwoB::s_health = 0;
		return true;
	}
	return false;
}

float TwoB::getHp()
{
	return TwoB::s_health;
}

float TwoB::getAtp()
{
	return TwoB::s_atp;
}

float TwoB::getMaxHP()
{
	return TwoB::s_max_health;
}

float TwoB::getSP()
{
	return TwoB::s_sp;
}

float TwoB::getMaxSP()
{
	return TwoB::s_max_sp;
}

bool TwoB::hasSP_(float cost)
{
	if ((TwoB::s_sp - cost < 0))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool TwoB::hasATP_()
{
	if ((TwoB::s_atp - 500 < 0))
	{
		return false;
	}
	else
	{
		TwoB::s_atp -= 500;
		return true;
	}
}




//----------------------9S Class----------------------
float NineS::s_max_health = 200;
float NineS::s_health = NineS::s_max_health;
float NineS::s_atp = 0;
float NineS::s_max_sp = 40;
float NineS::s_sp = NineS::s_max_sp;

const std::string NineS::s_ability_names[3] = { "9S Ability One", "9S Ability Two", "9S Ability Three" };
const std::string NineS::s_name = "9S";
NineS::NineS() :
	battle_idle_(*NineS::rectangle(), "./Textures/9S_Battle_Idle.png"),
	test_Animation_(*NineS::rectangle(), "./Textures/attack-sheet.png")
{
	animation_Controller_.addAnimation(battle_idle_);
	animation_Controller_.addAnimation(test_Animation_);
	animation_Controller_.getAnimation(0).setParameters(55, 150, 1, 4, 30); //0
	animation_Controller_.getAnimation(1).setParameters(100, 74, 2, 7, 4);
	setAttack(10);
	setDefense(10);
	setMaxHP(250);
	setHp(getMaxHP());

	//Loop Default (0) animation
	animation_Controller_.loopDefault(true);
}

void NineS::update()
{
	//<!> Changes color when attacking - DELETE LATER
	if (isAttacking())
	{
		rectangle()->setFillColor(sf::Color::Blue);
	}
	else {
		rectangle()->setFillColor(sf::Color::White);
	}
	//Handles ATP
	if (s_atp <= MAX_ATP) {
		s_atp++;
	}
	//isDead
	isDead();
	NineS::animation_Controller_.animate();
	NineS::handleDelay();
}

void NineS::render(sf::RenderWindow& window)
{
	window.draw(*NineS::rectangle());
}

void NineS::takeDamage(float damage)
{
	NineS::s_health -= damage;
}

std::string NineS::getAbilityName(int index)
{
	return NineS::s_ability_names[index];
}

std::string NineS::getName()
{
	return NineS::s_name;
}

void NineS::ability_attack(int attack, Entity& target)
{
	switch (attack)
	{
	case 0:
		ability_one(target);
		break;
	case 1:
		ability_two(target);
		break;
	case 2:
		ability_three(target);
		break;
	default:
		basic_attack(target);
	}
}

void NineS::basic_attack(Entity& target)
{
	if (!isAttacking())
	{
		//Play Audio
		a_instance.basic_damage_.play();
		//Do damage calculations
		target.setHp(target.getHp() - getAttack());
		setAttacking(true);
		animation_Controller_.start(1);
		setDelay(60);
		std::cout << "BASIC ATTACK\n";
	}
}

void NineS::ability_one(Entity& target)
{
	if (!isAttacking() && hasSP_(5) && hasATP_() )
	{
		target.setHp(target.getHp() - (getAttack() + 20));
		NineS::s_sp -= 5;
		setAttacking(true);
		animation_Controller_.start(0);
		setDelay(100);
		std::cout << "Ability One\n";
	}
}

void NineS::ability_two(Entity& target)
{
	if (!isAttacking() && hasSP_(10) && hasATP_() )
	{
		target.setHp(target.getHp() - (getAttack() + 50));
		NineS::s_sp -= 10;
		setAttacking(true);
		animation_Controller_.start(0);
		setDelay(180);
		std::cout << "Ability Two\n";
	}
}

void NineS::ability_three(Entity& target)
{
	if (!isAttacking() && hasSP_(15) && hasATP_() )
	{
		target.setHp(target.getHp() - (getAttack() + 70));
		NineS::s_sp -= 15;
		setAttacking(true);
		animation_Controller_.start(0);
		setDelay(300);
		std::cout << "Ability Three\n";
	}
}

bool NineS::isDead()
{
	
	if (NineS::s_health <= 0)
	{
		std::cout << "9S IS DEAD\n";
		NineS::s_health = 0;
		return true;
	}
	return false;
}

float NineS::getHp()
{
	return NineS::s_health;
}

float NineS::getAtp()
{
	return NineS::s_atp;
}

float NineS::getMaxHP()
{
	return NineS::s_max_health;
}

float NineS::getSP()
{
	return NineS::s_sp;
}

float NineS::getMaxSP()
{
	return NineS::s_max_sp;
}

bool NineS::hasSP_(float cost)
{
	if ((NineS::s_sp - cost < 0))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool NineS::hasATP_()
{
	if ((NineS::s_atp - 500 < 0))
	{
		return false;
	}
	else
	{
		NineS::s_atp -= 500;
		return true;
	}
}


//----------------------Machine Class----------------------
Enemy::Enemy()
{
	setAttack(5);
	setDefense(5);
	setMaxHP(100);
	setHp(getMaxHP());
	setAtp(0);
}

void Enemy::update()
{
		if (getAtp() <= MAX_ATP)
		{
			setAtp(getAtp() + 5);
		}
}

void Enemy::render(sf::RenderWindow& window)
{
	if (!isDead())
	{
		window.draw(*Enemy::rectangle());
	}
}

void Enemy::attack(Ally& target)
{
	target.takeDamage(getAttack());
	setAtp(0);
}