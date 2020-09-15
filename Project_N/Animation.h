#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
public:
	Animation(sf::RectangleShape&, std::string);
	void setParameters(int, int, int, int, int);
	void setIntRect();
	void animate();
	void setX(int);
	void setY(int);
	void start();
	void stop();
	void loop();
private:
	sf::RectangleShape* shape_;
	sf::Texture sprite_Sheet_;
	int columns_, rows_, width_, height_;
	//<!> X and Y may be uneccessary if we always assume they are 0.
	int x_ = 0, y_ = 0;
	int timer_ = 1;
	int total_time_;
	int currentSprite_ = 0;
	int currentRow_ = 0;
	int currentColumn_ = 0;
	int duration_;
	bool switchSprite_ = false;
	bool play_ = false;
	bool loop_ = false;
};

