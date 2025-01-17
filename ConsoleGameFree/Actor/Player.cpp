#include "Player.h"
#include "Engine/Engine.h"
#include "Engine/Timer.h"
#include "Game/Game.h"
#include "Level/GameLevel.h"

Player::Player(const Vector2& position, GameLevel* level)
	: DrawableActor("&"), refLevel(level)
{
	// 위치 설정.
	this->position = position;
	prePosition = position;

	// 색상 설정.
	color = Color::White;
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	static Timer timer(0.5f);

	// ESC 종료.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		// 메뉴 토글.
		Game::Get().ToggleMenu();
	}

	prePosition = position;

	if (Engine::Get().GetKeyUp(VK_SPACE) && Engine::Get().GetKey(VK_LEFT))
	{
		if (onSpace)
		{
			return;
		}
		if (refLevel->CanJump(Vector2(position.x - 1, position.y - 2 - boostCount)))
		{
			position.x -= 1;
			position.y -= (2 + boostCount);
		}
		timer.Reset();
		boostCount = 0;
	}

	if (Engine::Get().GetKeyUp(VK_SPACE) && Engine::Get().GetKey(VK_RIGHT))
	{
		if (onSpace)
		{
			return;
		}
		if (refLevel->CanJump(Vector2(position.x + 1, position.y - 2 - boostCount)))
		{
			position.x += 1;
			position.y -= (2 + boostCount);
		}
		timer.Reset();
		boostCount = 0;
	}

	if (Engine::Get().GetKey(VK_LEFT))
	{
		if (refLevel->CanPlayerMove(Vector2(position.x - 1, position.y)))
		{
			position.x -= 1;
		}
	}

	if (Engine::Get().GetKey(VK_RIGHT))
	{
		// 이동 가능한지 확인.
		if (refLevel->CanPlayerMove(Vector2(position.x + 1, position.y)))
		{
			position.x += 1;
		}
	}

	if (Engine::Get().GetKeyUp(VK_SPACE))
	{
		if (onSpace)
		{
			return;
		}
		if (refLevel->CanJump(Vector2(position.x, position.y - 2 - boostCount)))
		{
			position.y -= (2 + boostCount);
		}
		timer.Reset();
		boostCount = 0;
	}

	if (Engine::Get().GetKey(VK_SPACE))
	{
		timer.Update(deltaTime);
		if (timer.IsTimeOut())
		{
			boostCount = boostCount >= 5 ? 5 : ++boostCount;
			timer.Reset();
		}
	}
}

void Player::Draw()
{
	SetColor(color);

	Engine::Get().SetCursorPosition(prePosition);

	Log(" ");

	Engine::Get().SetCursorPosition(position);

	Log(image);
	onSpace = refLevel->OnSpace(position);
	if (onSpace)
	{
		position = Vector2(position.x, position.y + 1);
		Sleep(100);
	}

	// 색상 복구.
	SetColor(Color::White);
}
