#include "Animation.h"
//<!> Delete Later
#include <iostream>

//Constructor
Animation::Animation(sf::RectangleShape& shape, std::string filepath)
{
	//Get the rectangle shape
	Animation::shape_ = &shape;
	//Load the sprite sheet
	Animation::sprite_Sheet_.loadFromFile(filepath);
	

}

void Animation::setParameters(int width, int height, int rows, int columns, int duration)
{
	Animation::columns_ = columns;
	Animation::rows_ = rows;
	Animation::width_ = width;
	Animation::height_ = height;
	Animation::duration_ = duration;
	//Animation::shape_->setSize(sf::Vector2f(width, height));
	Animation::total_time_ = rows*columns*duration;
	Animation::setIntRect();
}

void Animation::setIntRect()
{
	//std::cout << "X: " << x_ + width_ * currentColumn_ << " Y: " << y_ + height_ * currentRow_ << "\n";
	Animation::shape_->setTextureRect(sf::IntRect(x_ + width_ * currentColumn_, y_ + height_ * currentRow_, width_, height_));
}

//Place in update function of entity
void Animation::animate()
{
	if (Animation::play_ == true)
	{
		int previousSprite = currentSprite_;
		Animation::currentSprite_ = timer_ / duration_;

		//If the sprite changes, switch em
		if (currentSprite_ != previousSprite)
		{
			currentColumn_++;
			if (currentColumn_ >= columns_)
			{
				currentRow_++;
				currentColumn_ = 0;
			}
			if (currentRow_ >= rows_)
			{
				currentRow_ = 0;
			}
			
			Animation::setIntRect();
		}
		//Reset Timer and Stop When Animation Ends;
		if (++timer_ >= total_time_)
		{
			timer_ = 0;
			if (loop_ == false)
			{
				stop();
			}
		}
	}

}

void Animation::setX(int x)
{
	Animation::x_ = x;
}

void Animation::setY(int y)
{
	Animation::y_ = y;
}

//Starts the Animation
void Animation::start()
{
	shape_->setSize(sf::Vector2f(width_, height_));
	//Apply sprite
	Animation::shape_->setTexture(&sprite_Sheet_);
	Animation::play_ = true;
	Animation::isFinished = false;
}

//Stops the Animation, Stops Loop, Resets Timer
void Animation::stop()
{
	Animation::play_ = false;
	Animation::loop_ = false;
	Animation::isFinished = true;
	Animation::timer_ = 0;
	Animation::currentRow_ = 0;
	Animation::currentColumn_ = 0;
	Animation::setIntRect();
}

void Animation::loop()
{
	Animation::loop_ = true;
	//Starts the animation if it isn't already playing
	if (Animation::play_ == false)
	{
		Animation::start();
	}
}
