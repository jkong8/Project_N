#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Animation_Controller.h"
#define MAX_ATP 1000
//Base Entity Class
class Entity
{
public:
	//Constructor
	Entity();
	//Game Loop Functions
	virtual void update() = 0;
	virtual void render(sf::RenderWindow&) = 0;
	//x and y position
	float* x();
	float* y();
	void setPosition(float, float);
	sf::RectangleShape* rectangle();
	virtual float getHp();
	virtual float getAtp();
	float getAttack();
	float getDefense();
	virtual float getMaxHP();
	float getMaxATP();
	void setHp(float);
	void setAtp(float);
	void setAttack(float);
	void setDefense(float);
	void setMaxHP(float);
	virtual bool isDead();
	bool atpFull();
private:
	float x_, y_;
	sf::RectangleShape rectangle_;
	int maxHp_;
	int health_;
	int atp_ = 0;
	int attack_;
	int defense_;
};

class Ally : public Entity
{
public:
	virtual void ability_attack(int, Entity&) = 0;
	virtual void basic_attack(Entity&) = 0;
	virtual void ability_one(Entity&) = 0;
	virtual void ability_two(Entity&) = 0;
	virtual void ability_three(Entity&) = 0;
	bool isAttacking();
	void setAttacking(bool);
	void setDelay(int);
	void handleDelay();
	virtual void takeDamage(float) = 0;
	virtual float getSP() = 0;
	virtual float getMaxSP() = 0;
	virtual std::string getAbilityName(int) = 0;
	virtual std::string getName() = 0;
private:

	bool attacking_;
	int delay_;
};

//A2 Subclass <!> study Static Classes
class ATwo : public Ally
{
public:
	//Constructor
	ATwo();
	//Game Loop Methods
	virtual void update();
	virtual void render(sf::RenderWindow&);
	virtual void takeDamage(float);
	virtual std::string getAbilityName(int);
	virtual std::string getName();
	void ability_attack(int, Entity&);
	void basic_attack(Entity&);
	void ability_one(Entity&);
	void ability_two(Entity&);
	void ability_three(Entity&);
	bool isDead();
	float getHp();
	float getAtp();
	float getMaxHP();
	float getSP();
	float getMaxSP();
	static float s_health;
	static float s_max_health;
	static float s_atp;
	static float s_sp;
	static float s_max_sp;

	static const std::string s_ability_names[3];
	static const std::string s_name;
	Animation_Controller animation_Controller_;

private:
	//Animate <!> Contains Test Animations
	Animation test_Animation_;
	bool hasSP_(float);
	bool hasATP_();

};

//2B Subclass <!> Study Static Classes
class TwoB : public Ally
{
public:
	//Constructor
	TwoB();
	//Game Loop Methods
	virtual void update();
	virtual void render(sf::RenderWindow&);
	virtual void takeDamage(float);
	virtual std::string getAbilityName(int);
	virtual std::string getName();

	void ability_attack(int, Entity&);
	void basic_attack(Entity&);
	void ability_one(Entity&);
	void ability_two(Entity&);
	void ability_three(Entity&);
	bool isDead();
	float getHp();
	float getAtp();
	float getMaxHP();
	float getSP();
	float getMaxSP();
	static float s_health;
	static float s_atp;
	static float s_max_health;
	static float s_sp;
	static float s_max_sp;

	static const std::string s_ability_names[3];
	static const std::string s_name;
	Animation_Controller animation_Controller_;

private:
	//Animate <!> Contains Test Animations
	Animation test_Animation_;
	bool hasSP_(float);
	bool hasATP_();

};



//9S Subclass <!> study Static Classes
class NineS : public Ally
{
public:
	//Constructor
	NineS();
	//Game Loop Methods
	virtual void update();
	virtual void render(sf::RenderWindow&);
	virtual void takeDamage(float);
	virtual std::string getAbilityName(int);
	virtual std::string getName();
	bool isDead();
	float getHp();
	float getAtp();
	float getMaxHP();
	float getSP();
	float getMaxSP();
	void ability_attack(int, Entity&);
	void basic_attack(Entity&);
	void ability_one(Entity&);
	void ability_two(Entity&);
	void ability_three(Entity&);
	static float s_health;
	static float s_max_health;
	static float s_atp;
	static float s_sp;
	static float s_max_sp;

	static const std::string s_ability_names[3];
	static const std::string s_name;
	Animation_Controller animation_Controller_;
private:
	//Animate <!> Contains Test Animations
	Animation test_Animation_;
	bool hasSP_(float);
	bool hasATP_();
};
//Machine Subclass
class Enemy : public Entity
{
public:
	//Constructor
	Enemy();
	//Game Loop Methods
	virtual void update();
	virtual void render(sf::RenderWindow&);
	virtual void attack(Ally&);
private:
};