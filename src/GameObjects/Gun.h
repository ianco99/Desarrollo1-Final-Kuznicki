#pragma once
#include "raylib.h"

#include "Bullet.h"

namespace kuznickiGameObjects
{
	static const int maxBullets = 200;

	class Gun
	{
	private:
		Rectangle* myPlayer;
		Bullet bullets[maxBullets];

		Texture sprite;

		Vector2 position;
		float angle;

		bool canShoot = false;
		int currentBullets;
		int maxBulletCount;

	public:
		Gun(Rectangle& myNewPlayer);
		~Gun();

		void Update(Rectangle myNewPlayer);
		void PointGun();

		void ToggleCanShoot(bool value);

		void PullTrigger(Rectangle playerBody);
		void Shoot(Rectangle playerBody);

		Vector2 GetBulletDirection(Rectangle playerBody);
		float GetBulletRotation(Vector2 distance);

		Bullet* GetBulletByIndex(int index);
		void DestroyBulletByIndex(int index);
		int GetMaxBullets();
		int GetMaxBulletCount();
		int GetCurrentBulletCount();
		Vector2 GetPosition();

		void Draw(Rectangle playerBody);
	};
}