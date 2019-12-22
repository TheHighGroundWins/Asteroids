#pragma once
#include "Asteroid.h"
#include <sfml/Graphics.hpp>
using namespace sf;
class Asteroids
{
public:
	Asteroids();
	void setup(Vector2f resolution);
	Asteroid asteroids[10];
	void update(Clock deltaTime);
};

