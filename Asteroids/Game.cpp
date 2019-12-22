// Hello SFML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sfml/Graphics.hpp>
#include "Player.h"

int main()
{
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	VideoMode vm(resolution.x, resolution.y);
	RenderWindow window(vm, "Asteroids", Style::Resize);

	Player p1(resolution);

	while (window.isOpen())
	{
		Clock deltaTime;
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		p1.updatePlayer(deltaTime);
		window.clear();
		
		if (p1.getAliveStatus())
		{
		window.draw(p1.getShape());
		}
		if(p1.retry)
		{
			window.draw(p1.getGameOver());
		}

		window.draw(p1.getLives());
		window.draw(p1.getScore());

		for (int i = 0;i < 3;i++)
		{
		window.draw(p1.laser.bullets[i]);
		}
		for (int i = 0;i < 10;i++)
		{
			if (p1.asteroids.asteroids[i].health==0)
			{
			window.draw(p1.asteroids.asteroids[i].asteroidSprite);
			}
		}
		
		window.display();
	}
    return 0;
}

