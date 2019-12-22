#pragma once
#include <sfml/Graphics.hpp>
using namespace sf;
class Asteroid
{
public:
	Asteroid();
	Sprite asteroidSprite;
	int region;
	Vector2f move;
	Vector2f firstPos;
	void setup(Vector2f resolutionIn);
	void update(Clock deltaTime);
	void setPos();
	int box;
	int health = 0;
private:
	
	Texture asteroidTexture;
	Vector2f resolution;
	
};

