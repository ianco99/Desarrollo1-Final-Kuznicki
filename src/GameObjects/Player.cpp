#include "raylib.h"
#include "Player.h"
#include "Gun.h"

namespace kuznickiGameObjects
{
	Player::Player(float posX, float posY, float sizeX, float sizeY, Color givenColor)
	{
		this->body = new Rectangle{ posX, posY, sizeX, sizeY };
		this->color = givenColor;

		this->gun = Gun(this->body);
	}

	Player::~Player()
	{

	}

	void Player::Update()
	{
		this->gun.Update();
	}

	void Player::Reposition(float newX, float newY)
	{
		body->x = newX;
		body->y = newY;
	}

	Gun* Player::GetGun()
	{
		return &gun;
	}

	void Player::ShootGun()
	{
		this->gun.PullTrigger();
		//maybe play an anim
	}

	void Player::Draw()
	{
		DrawRectangleRec(*body, color);

		gun.Draw();
	}

	Rectangle Player::GetBody()
	{
		return *body;
	}
}