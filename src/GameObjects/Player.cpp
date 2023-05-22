#include "raylib.h"
#include "Player.h"

using namespace kuznickiGameObjects;

Player::Player(float posX, float posY, float sizeX, float sizeY, Color givenColor)
{
	this->body = { posX, posY, sizeX, sizeY };
	this->color = givenColor;
}

Player::~Player()
{

}

void Player::Reposition(float newX, float newY)
{
	body.x = newX;
	body.y = newY;
}

void Player::ShootGun()
{
	this->gun.Shoot();
	//maybe play an anim
}

void Player::Draw()
{
	DrawRectangleRec(body, color);
}

Rectangle Player::GetBody()
{
	return body;
}