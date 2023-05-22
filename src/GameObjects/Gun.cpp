#include "Gun.h"
#include <iostream>

using namespace kuznickiGameObjects;
Gun::Gun()
{
}

Gun::~Gun()
{
}

void Gun::ToggleCanShoot(bool value)
{
	canShoot = value;
}

void Gun::Shoot()
{
	std::cout << "god";
}