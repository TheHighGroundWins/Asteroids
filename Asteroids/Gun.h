#pragma once
#include <sfml/Graphics.hpp>
using namespace sf;
class Gun
{
public:
	Gun();
	void setResoltuon(Vector2f resolutionIn);
	void shoot(Vector2f playerPosition, float playerRotation, Time fps);
	int isBulletAvailable(Vector2f playerPosition);
	RectangleShape bullets[3];
	void update(Time fps);
	bool canShoot[2];

private:
	Vector2f resolution;
	Clock fireRate;
	bool notOverHeated = true;
	bool updateBullet = false;
	Vector2f bulletSpeed;
	int bulletStack = 0;
	int activeBullet = 0;
	Vector2f moveDirections[2];
};

