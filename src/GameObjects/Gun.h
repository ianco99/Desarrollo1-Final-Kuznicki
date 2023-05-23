#pragma once
#include "raylib.h"

//#include "Player.h"

namespace kuznickiGameObjects
{
	const int maxBullets = 200;

	class Gun
	{
	private:
		Rectangle* myPlayer;
		Rectangle bullets[maxBullets];
		bool canShoot = false;

	public:
		Gun();
		Gun(Rectangle* myPlayer);
		~Gun();

		void Update();

		void ToggleCanShoot(bool value);

		void PullTrigger();
		void Shoot();

		void Draw();
	};
}