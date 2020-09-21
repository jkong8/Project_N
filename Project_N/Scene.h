#pragma once
#include "Actor.h"
#include "SFML/Graphics.hpp"
#include "Audio_Manager.h"
//Base Class
//<!> MIGHT NEED ACTOR VECTOR
class Scene
{
public:
	Scene();
	~Scene();
	virtual void update() = 0;
	virtual void render(sf::RenderWindow&) = 0;
	void finish(int, int);
	void reset();
	bool isFinished();
	
	
	int timer = 0;
	bool finished = false;;
private:
	Audio_Manager& a_instance_ = Audio_Manager::getInstance();
};

class Scene_One : public Scene
{
public:
	Scene_One();
	void update();
	void render(sf::RenderWindow&);
private:
	Actor aTwo;
	Actor twoB;
};

