#include "raylib.h"
#include "Player.h"
#include "Gun.h"

namespace kuznickiGameObjects
{
	Player::Player(float posX, float posY, float sizeX, float sizeY, Color givenColor)
	{
		this->body = new Rectangle{ posX, posY, sizeX, sizeY };
		this->color = givenColor;

		this->gun = Gun(body);

		sprite = LoadTexture("../rsc/adventurer-idle-00.png");
	}

	Player::~Player()
	{

	}

	void Player::Update()
	{
		if (showingDamage == true)
		{
			damageColorCurrentTimer += GetFrameTime();
			color = RED;

			if (damageColorCurrentTimer >= damageColorMaxTimer)
			{
				color = WHITE;
				showingDamage = false;
			}
		}

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
		//DrawRectangleRec(*body, color);
		Rectangle spriteSource = { 0.0f,0.0f, sprite.width, sprite.height };
		Rectangle spriteDestination = { body->x + body->width / 2,body->y + body->height / 2, sprite.width * 3.8f, sprite.height * 3.5f };
		Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

		//DrawRectanglePro(bullets[i].GetRadius(), spriteOrigin, bullets[i].GetAngle(), bullets[i].GetColor());
		DrawTexturePro(sprite, spriteSource, spriteDestination, spriteOrigin, 0.0f, color);

		gun.Draw();
	}

	Rectangle Player::GetBody()
	{
		return *body;
	}

	void Player::Damage(int damage)
	{
		this->lives -= damage;

		StartDamageTimer();

		if (lives <= 0)
		{
			isAlive = false;
		}
	}

	void Player::StartDamageTimer()
	{
		damageColorCurrentTimer = 0;
		showingDamage = true;
	}

	bool Player::GetIsAlive()
	{
		return isAlive;
	}

	void Player::SetIsAlive(bool value)
	{
		this->isAlive = value;
	}
}