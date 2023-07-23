#pragma once
#include "raylib.h"

#include "Bullet.h"

namespace kuznickiGameObjects
{
	const int maxBullets = 200;

	class Gun
	{
	private:
		Rectangle* myPlayer;
		Bullet bullets[maxBullets];
		bool canShoot = false;
		int currentBullets;
		int maxBulletCount;

	public:
		Gun(Rectangle* myPlayer);
		~Gun();

		void Update();

		void ToggleCanShoot(bool value);

		void PullTrigger();
		void Shoot();

		Vector2 GetBulletDirection();
		float GetBulletRotation(Vector2 distance);

		Bullet* GetBulletByIndex(int index);
		void DestroyBulletByIndex(int index);
		int GetMaxBullets();

		void Draw();
	};
}