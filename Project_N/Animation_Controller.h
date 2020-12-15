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
	void loopDefault(bool);
private:
	//Vector of Animations
	std::vector<Animation> animations_;
	bool loop_d_ = false;
	int currentAnimation_ = 0;
	//DEFAULT ANIMATION IS 0
	const int defaultAnimation = 0;
};

