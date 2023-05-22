#include "raylib.h"
#include "Player.h"

using namespace kuznickiGameObjects;

Player::Player(float posX, float posY,float sizeX, float sizeY, Color givenColor)
{
	this->body = { posX, posY, sizeX, sizeY };
	this->color = givenColor;
}

Player::~Player()
{

}

void Player::Draw()
{
	DrawRectangleRec(body, color);
}