#include "Animation_Controller.h"



Animation_Controller::Animation_Controller()
{
}

//Animates the Current Animation
void Animation_Controller::animate()
{
	animations_[currentAnimation_].animate();
}

//Adds Animation to Vector
void Animation_Controller::addAnimation(Animation& animation)
{
	animations_.push_back(animation);
}

//Returns the Animation from Vector (Usually to Paramatize the Animation)
Animation& Animation_Controller::getAnimation(int index)
{
	return animations_[index];
}

void Animation_Controller::start(int index)
{
	//If different animation, stop it then start new one
	if (index != currentAnimation_)
	{
		animations_[currentAnimation_].stop();
		currentAnimation_ = index;
	}
	//If it isn't different just start it
	animations_[currentAnimation_].start();
}

void Animation_Controller::loop(int index)
{
	//If different animation, loop it then start new one
	if (index != currentAnimation_)
	{
		animations_[currentAnimation_].stop();
		currentAnimation_ = index;
	}
	//If it isn't different just loop it
	animations_[currentAnimation_].loop();
}

void Animation_Controller::stop()
{
	animations_[currentAnimation_].stop();
}

bool Animation_Controller::isEmpty()
{
	if (animations_.size() <= 0)
	{
		return true;
	}

	return false;
}