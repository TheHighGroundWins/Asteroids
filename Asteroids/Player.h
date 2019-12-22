#pragma once
#include <sfml/Graphics.hpp>
#include "Gun.h"
#include "Asteroids.h"

using namespace sf;

class Player
{
public:
	Player(Vector2f resolutionIn);
	void thrust(Clock deltaTime);
	void turnLeft();
	void turnRight();
	Sprite getShape();
	void updatePlayer(Clock deltaTime);
	Gun laser;
	Asteroids asteroids;
	Text getScore();
	bool getAliveStatus();
	Text getGameOver();
	Text getLives();
	bool retry = false;

private:
	bool isAlive = true;
	Sprite playerTriangle;
	Vector2f lastCoordinates;
	Texture playerTexture;
	Vector2f resolution;
	bool constantMove = false;
	bool newRotation = true;
	float saveX;
	float saveY;
	double momentumX=0.020;
	double momentumY=0.020;
	Clock floatClock;
	Text score;
	Text gameOver;
	Text livesText;
	Font font;
	int scoreInt=00;
	int lives = 3;
	Vector2f asteroidSpeed[10];
	
};

