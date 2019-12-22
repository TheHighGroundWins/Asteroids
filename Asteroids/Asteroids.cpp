#include "stdafx.h"
#include "Asteroids.h"
#include "Asteroid.h"

Asteroids::Asteroids()
{
	srand(time(0));
}
//creates the random location of the asteroids
void Asteroids::setup(Vector2f resolution)
{
	//sets up all the asteroids
	for (int i = 0; i < 10;i++)
	{
		asteroids[i].setup(resolution);
		//determines a random region for each asteroid
		int region = rand() % 4 + 1;
		//determines a random position in each region
		//sets the direction of the movments based on the location of each asteroid
		if (region == 1)
		{
			int x = asteroids[i].asteroidSprite.getPosition().x - asteroids[i].box;
			asteroids[i].firstPos.x = rand() % x;
			int y = resolution.y;
			asteroids[i].firstPos.y = rand() % y;

			//sets the move direction
			asteroids[i].move.x = 0.001;

			//sets a random y move direction
			int direction = rand() % 1;
			if (direction == 0)
			{
				asteroids[i].move.y = -0.001;
			}
			if (direction == 1)
			{
				asteroids[i].move.y = 0.001;
			}
		}
		if (region == 2)
		{
			int min = asteroids[i].asteroidSprite.getPosition().x - asteroids[i].box;
			int diff = (asteroids[i].asteroidSprite.getPosition().x + asteroids[i].box + 1)-min;
			asteroids[i].firstPos.x = rand() % diff + min;
			int y = asteroids[i].asteroidSprite.getPosition().y - asteroids[i].box;
			asteroids[i].firstPos.y = rand() % y;
			//sets the move direction
			asteroids[i].move.y = 0.001;
			//sets a random x move direction
			int direction = rand() % 1;
			if (direction == 0)
			{
				asteroids[i].move.x = -0.001;
			}
			if (direction == 1)
			{
				asteroids[i].move.x = 0.001;
			}
		}
		if (region == 3)
		{
			int min = asteroids[i].asteroidSprite.getPosition().x + asteroids[i].box;
			int diff = resolution.x - min + 1;
			asteroids[i].firstPos.x = rand() % diff + min;
			int y = resolution.y;
			asteroids[i].firstPos.y = rand() % y;
			//sets the move direction
			asteroids[i].move.x = -0.001;
			//sets a random y move direction
			int direction = rand() % 1;
			if (direction == 0)
			{
				asteroids[i].move.y = -0.001;
			}
			if (direction == 1)
			{
				asteroids[i].move.y = 0.001;
			}
		}
		if (region == 4)
		{
			int minX = asteroids[i].asteroidSprite.getPosition().x - asteroids[i].box;
			int x = resolution.x;
			int diffX = x - minX + 1;
			asteroids[i].firstPos.x = rand() % diffX + minX;
			int minY = asteroids[i].asteroidSprite.getPosition().y + asteroids[i].box;
			int diffY = asteroids[i].asteroidSprite.getPosition().y - minY + 1;
			asteroids[i].firstPos.y = rand() % diffY + minY;
			//sets the move direction
			asteroids[i].move.y = -0.001;

			//sets a random x move direction
			int direction = rand() % 1;
			if (direction == 0)
			{
				asteroids[i].move.x = -0.001;
			}
			if (direction == 1)
			{
				asteroids[i].move.x = 0.001;
			}
		}
		//gives the resolution of screen to each asteroid
		//and sets the position of the sprite
		asteroids[i].setPos();
	}

}

void Asteroids::update(Clock deltaTime)
{
	for (int i = 0;i < 10; i++)
	{
		if (asteroids[i].health == 0)
		{
		asteroids[i].update(deltaTime);
		}
	}
}
