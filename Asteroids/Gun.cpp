#include "stdafx.h"
#include "Gun.h"


Gun::Gun()
{
	//sets all bullets to white and offscreen
	for (int i = 0; i < 3;i++)
	{
		bullets[i].setSize(Vector2f(5,5));
		bullets[i].setPosition(-100,-100);
	}
	for (int i = 0; i < 3;i++)
	{
		canShoot[i] = true;
	}
}
void Gun::setResoltuon(Vector2f resolutionIn)
{
	resolution = resolutionIn;
}

void Gun::shoot(Vector2f playerPosition,float playerRotation,Time fps)
{
	//checks if bullets are available
	activeBullet = isBulletAvailable(playerPosition);
	

	//teleports bullet to player
	//shoots the specified bullet
	//if it is in the firerate
	if (activeBullet >= 0&&notOverHeated)
	{
		float moveX = 0.1 * cos((3.1415 / 180)*(playerRotation));
		float moveY = 0.1 * sin((3.1415 / 180)*playerRotation);
		bulletSpeed.x = moveX;
		bulletSpeed.y = moveY;
		bullets[activeBullet].setPosition(playerPosition);
		moveDirections[activeBullet].x = bulletSpeed.x;
		moveDirections[activeBullet].y = bulletSpeed.y;
		canShoot[activeBullet] = true;
		
		fireRate.restart();
		updateBullet = true;
	}
	Time fireTime = fireRate.getElapsedTime();
	//else does nothing
	if (fireTime.asSeconds()<0.5)
	{
		notOverHeated = false;
	}
	else
	{
		notOverHeated = true;
		fireRate.restart();
	}

}

void Gun::update(Time fps)
{
	for (int i = 0; i <= 2;i++)
	{
		if (canShoot[i])
		{
			bullets[i].move(moveDirections[i].x*fps.asMicroseconds(), moveDirections[i].y*fps.asMicroseconds());
			bullets[i].setFillColor(Color::White);
		}
	}
}


int Gun::isBulletAvailable(Vector2f playerPosition)
{
	int match = -1;
	//checks if any of the bullets have gone through
	//the walls therefore is available
	for (int i = 0; i <= 2;i++)
	{
		if (bullets[i].getPosition().x==-100)
		{
			match = i;
			break;
		}
		if (bullets[i].getPosition().y < 0)
		{
			match = i;
			break;
		}
		if (bullets[i].getPosition().y >resolution.y)
		{
			match = i;
			break;
		}
		if (bullets[i].getPosition().x >resolution.x)
		{
			match = i;
			break;
		}
		if (bullets[i].getPosition().x <0)
		{
			match = i;
			break;
		}
	}
	return match;
}