#include "RunGame.h"
#include "raylib.h"
#include "Player.h"

using namespace kuznickiSystem;
using namespace kuznickiGameObjects;

RunGame::RunGame()
{

}

RunGame::~RunGame()
{
}

void RunGame::Start()
{
	InitWindow(1024, 768, "MyFinal");

	Player player = Player(GetScreenWidth() / 2, GetScreenHeight() / 2, 20,20,WHITE);

	while (true)
	{
		BeginDrawing();
		ClearBackground(BLACK);
		player.Draw();
		EndDrawing();
	}
}