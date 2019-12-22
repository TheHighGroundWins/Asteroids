#include "stdafx.h"
#include "Asteroid.h"


Asteroid::Asteroid()
{
	asteroidTexture.loadFromFile("Assets/asteroid.png");
	asteroidSprite.setTexture(asteroidTexture);
}

//sets the Asteroid's first position
//and sets the resolution of the screen
void Asteroid::setup(Vector2f resolutionIn)
{
	resolution = resolutionIn;
	box = resolution.y / 6;
	health = 0;
}

void Asteroid::setPos()
{
	asteroidSprite.setPosition(firstPos);
}

//constantly moves the asteroid
//and prevents goes through one side forever
void Asteroid::update(Clock deltaTime)
{
	Time delta = deltaTime.getElapsedTime();
	float x = move.x*delta.asMicroseconds();
	float y = move.y*delta.asMicroseconds();
	asteroidSprite.move(x,y);
	if (asteroidSprite.getPosition().y < 10)
	{
		// teleports players to the bottom
		float x = asteroidSprite.getPosition().x;
		asteroidSprite.setPosition(x, resolution.y - 10);

	}
	//prevents going through the bottom
	if (asteroidSprite.getPosition().y > resolution.y - 10)
	{
		// teleports asteroid to the top
		float x = asteroidSprite.getPosition().x;
		asteroidSprite.setPosition(x, 10);
	}
	//prevents going through the left side
	if (asteroidSprite.getPosition().x < 10)
	{
		// teleports asteroid to the right side
		float y = asteroidSprite.getPosition().y;
		asteroidSprite.setPosition(resolution.x - 10, y);
	}

	//prevents going through the right side
	if (asteroidSprite.getPosition().x > resolution.x - 10)
	{
		// teleports astoid to the left side
		float y = asteroidSprite.getPosition().y;
		asteroidSprite.setPosition(10, y);
	}
}

