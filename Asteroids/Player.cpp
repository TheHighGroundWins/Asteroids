#include "stdafx.h"
#include "Player.h"
#include <sfml/Graphics.hpp>
#include <math.h>
#include "Gun.h"
#include <string> 

using namespace sf;
Player::Player(Vector2f resolutionIn)
{
	//Creates the player triangle
	playerTriangle.setPosition(500,500);
	playerTriangle.setOrigin(20,30);
	//saves the first last coordinates
	lastCoordinates = playerTriangle.getPosition();


	//sets the image of the texture
	playerTexture.loadFromFile("Assets/ship.png");
	//set the texture of the triangle
	playerTriangle.setTexture(playerTexture);
	playerTriangle.setScale(Vector2f(0.30,0.30));
	playerTriangle.setRotation(-90);

	resolution = resolutionIn;
	laser.setResoltuon(resolution);
	asteroids.setup(resolution);

	//sets the score font,size and color
	
	font.loadFromFile("fonts/cour.ttf");

	score.setFont(font);
	score.setFillColor(Color::White);
	score.setCharacterSize(100);
	score.setPosition(50,50);
	score.setString(std::to_string(scoreInt));
	//sets the game over screen font color and size
	gameOver.setFont(font);
	gameOver.setFillColor(Color::White);
	gameOver.setCharacterSize(200);
	gameOver.setPosition(500,500);
	gameOver.setString("Game Over");

	//show the player lives
	livesText.setFont(font);
	livesText.setFillColor(Color::White);
	livesText.setCharacterSize(100);
	livesText.setPosition(200, 50);
	livesText.setString("Lives: "+std::to_string(lives));
}

void Player::thrust(Clock deltaTime)
{
	
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		Time fps = deltaTime.getElapsedTime();
		
		//moves the player forward in the direction they're facing
		float moveX =  0.025 * cos((3.1415/180)*(playerTriangle.getRotation()));
		float moveY = 0.025 * sin((3.1415/ 180)*playerTriangle.getRotation());

		playerTriangle.move(moveX*fps.asMicroseconds(),moveY*fps.asMicroseconds());
		constantMove = true;
		newRotation = true;
		floatClock.restart();
	}

	if (newRotation)
	{
		saveX = playerTriangle.getRotation();
		saveY = playerTriangle.getRotation();
		momentumX = 0.020;
		momentumY = 0.020;
		newRotation = false;
		
	}
	if (constantMove)
	{
		Time fps = deltaTime.getElapsedTime();


		//moves the player forward in the direction they're facing
		float moveX = momentumX* cos((3.1415 / 180)*(saveX));
		float moveY = momentumY * sin((3.1415 / 180)*(saveY));

		playerTriangle.move(moveX*fps.asMicroseconds(), moveY*fps.asMicroseconds());
	}
	Time floatTime = floatClock.getElapsedTime();
	if (floatTime.asSeconds() >=1)
	{
		momentumX -= 0.01;
		momentumY -= 0.01;
		floatClock.restart();
	}
	if (momentumX < 0 || momentumY < 0)
	{
		momentumX = 0;
		momentumY = 0;
	}
}
void Player::turnLeft()
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		playerTriangle.rotate(-0.5);
	}
}

void Player::turnRight()
{
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		playerTriangle.rotate(0.5);
	}
}

Sprite Player::getShape()
{
	return playerTriangle;
}

Text Player::getScore()
{
	return score;
}

Text Player::getGameOver()
{
	return gameOver;
}

bool Player::getAliveStatus()
{
	return isAlive;
}

Text Player::getLives()
{
	return livesText;
}

void Player::updatePlayer(Clock deltaTime)
{
	//movement
	//prevents moving after getting destroyed
	if (isAlive)
	{
		thrust(deltaTime);
		turnLeft();
		turnRight();


		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			Time fps = deltaTime.getElapsedTime();
			laser.shoot(playerTriangle.getPosition(), playerTriangle.getRotation(), fps);
		}
	}
	if(retry)
	{
		//if dead give game over screen and option to restart
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			scoreInt = 0;
			retry = false;
			isAlive = true;
			lives = 3;
			score.setString(std::to_string(scoreInt));
			livesText.setString("Lives: " + std::to_string(lives));
		}
	}
	asteroids.update(deltaTime);
	if (isAlive)
	{
		laser.update(deltaTime.getElapsedTime());
	}
	//checks if teh player hits an asteroid
	for (int i = 0;i < 2;i++)
	{
		for (int a = 0; a < 10;a++)
		{
			if (asteroids.asteroids[a].health==0)
			{
				if (asteroids.asteroids[a].asteroidSprite.getGlobalBounds().intersects(laser.bullets[i].getGlobalBounds()))
				{
					scoreInt++;
					asteroids.asteroids[a].health--;
					score.setString(std::to_string(scoreInt));
					laser.bullets[i].setPosition(-100, -100);
					laser.canShoot[i] = false;
				}
			}
		}
	}

	//checks if the player is hit by an asteroid
	for (int i = 0;i < 10;i++)
	{
		if (asteroids.asteroids[i].health == 0)
		{
			if (isAlive)
			{
				if (playerTriangle.getGlobalBounds().intersects(asteroids.asteroids[i].asteroidSprite.getGlobalBounds()))
				{
					lives--;
					livesText.setString("Lives: " + std::to_string(lives));
					isAlive = false;
				}
			}
		}
	}
	
	if (lives == 0)
	{
		retry = true;
	}
	//if the player dies reset the position
	if (lives > 0)
	{
		if (!isAlive)
		{
			playerTriangle.setPosition(500,500);
			isAlive = true;
		}
	}
	int all = 0;
	for (int i = 0; i < 10; i++)
	{
		if (asteroids.asteroids[i].health <= 0)
		{
			all++;
		}
	}
	
	if (scoreInt % 10==0&& !scoreInt==0)
	{
		asteroids.setup(resolution);
		scoreInt++;
		for (int i = 0;i < 10;i++)
		{
			asteroidSpeed[i] = asteroids.asteroids[i].move;
			asteroidSpeed[i].x *= 4;
			asteroidSpeed[i].y *= 4;
			asteroids.asteroids[i].move=asteroidSpeed[i];
		}
	}
	
	//checks of wall collisions
	//prevent from going through the top
	if (playerTriangle.getPosition().y < 10)
	{
		// teleports players to the bottom
		float x = playerTriangle.getPosition().x;
		playerTriangle.setPosition(x,resolution.y-10);

	}
	//prevents going through the bottom
	else if (playerTriangle.getPosition().y > resolution.y-10)
	{
		// teleports players to the top
		float x = playerTriangle.getPosition().x;
		playerTriangle.setPosition(x, 10);
	}
	//prevents going through the left side
	else if (playerTriangle.getPosition().x < 10)
	{
		// teleports players to the right side
		float y = playerTriangle.getPosition().y;
		playerTriangle.setPosition(resolution.x-10,y);
	}

	//prevents going through the right side
	else if (playerTriangle.getPosition().x > resolution.x-10)
	{
		// teleports players to the left side
		float y = playerTriangle.getPosition().y;
		playerTriangle.setPosition(10, y);
	}
	

	//updates the last set off coordinates for wall detection
	lastCoordinates=playerTriangle.getPosition();
}

