#pragma once

namespace kuznickiGameObjects
{
	const int maxBullets = 200;

	class Gun
	{
	private:
		int bullets[maxBullets];
		bool canShoot = false;

	public:
		Gun();
		~Gun();

		void ToggleCanShoot(bool value);
		
		void Shoot();
	};
}