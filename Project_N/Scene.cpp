#include "Scene.h"
#include <iostream>
//Base Class
Scene::Scene() 
{

}

Scene::~Scene()
{

}

void Scene::finish(int time_point, int timer)
{
	if (time_point == timer)
	{
		finished = true;
	}
}

void Scene::reset()
{
	timer = 0;
	finished = false;
}

bool Scene::isFinished()
{
	return finished;
}

//-----------------------Scene One-----------------------------
Scene_One::Scene_One() : 
	aTwo("A2", sf::Vector2f(100,200)),
	twoB("2B", sf::Vector2f(100, 400))
{
	
}

void Scene_One::update()
{
	//Update ALL actors then write the "script"
	aTwo.update();
	twoB.update();
	timer++;
	
	aTwo.say("...", 300, 120, timer);
	aTwo.say("I... am still alive...", 420, 300, timer);
	aTwo.say("Wait a second... is that?!", 720, 240, timer);
	aTwo.moveTo(sf::Vector2f(150, 400), 2, 1000, timer);

	twoB.say("ugh... what is going on?", 1120, 300, timer);
	twoB.say("A2!!! What is going on here?!", 1420, 240, timer);

	aTwo.say("No time to talk. Seems like we have hostiles incoming.", 1660, 300, timer);
	aTwo.say("Come on, let's talk afterwards.", 1960, 240, timer);

	twoB.say("Roger.", 2200, 120, timer);

	aTwo.moveTo(sf::Vector2f(1000, 400), 2, 2260, timer);
	twoB.moveTo(sf::Vector2f(950, 400), 2, 2290, timer);

	aTwo.say("They are here!", 2800, 200, timer);
	//Finish Scene at the 20th second
	finish(3000, timer);
	//<!> DELETE LATER AND IMPLEMENT BETTER
	if (finished)
	{
		aTwo.reset();
		twoB.reset();
	}
}

void Scene_One::render(sf::RenderWindow& window)
{
	aTwo.render(window);
	twoB.render(window);
}
