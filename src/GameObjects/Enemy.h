#pragma once
#include "raylib.h"

class Enemy
{
private:
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float radius;

	Color color;

	int damage;


public:
	Enemy();
	~Enemy();
};
