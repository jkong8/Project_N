#pragma once
#include "Animation.h"
#include <vector>
class Animation_Controller
{
public:
	Animation_Controller();
	void animate();
	void addAnimation(Animation&);
	Animation& getAnimation(int);
	void start(int);
	void loop(int);
	void stop();
	bool isEmpty();
private:
	//Vector of Animations
	std::vector<Animation> animations_;
	int currentAnimation_ = 0;
	const int defaultAnimation = 0;
};

