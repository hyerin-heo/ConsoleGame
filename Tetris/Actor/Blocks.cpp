#include "Blocks.h"
#include "Level/Tetris1Level.h"
#include <Engine/Timer.h>
#include <Engine/Engine.h>
#include <Game/Game.h>

Blocks::Blocks(bool** block, Tetris1Level* refLevel, float speed)
{
	this->block = block;
	// 위치 설정.
	this->position = Vector2(Engine::Get().ScreenSize().x * 0.5f, 1);
	this->prePosition = position;

	color = Random(1, 80);
	isDone = false;
	this->refLevel = refLevel;
	this->speed = speed;
}

Blocks::~Blocks()
{
	if (block)
	{
		for (int ix = 0; ix < 3; ++ix)
		{
			delete[] block[ix];
		}

		delete block;
	}
}

void Blocks::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		// 메뉴 토글.
		Game::Get().ToggleMenu();
	}
	prePosition = position;

	static Timer timer(speed);

	timer.Update(deltaTime);

	if (refLevel->IsEnd(Vector2(position.x, position.y)))
	{
		refLevel->GameOver();
	}

	if (Engine::Get().GetKeyDown(VK_LEFT))
	{
		if (!refLevel->IsEnd(Vector2(position.x - 1, position.y)))
		{
			position.x -= 1;
		}
	}

	if (Engine::Get().GetKeyDown(VK_RIGHT))
	{
		if (!refLevel->IsEnd(Vector2(position.x + 1, position.y)))
		{
			position.x += 1;
		}
	}

	if (timer.IsTimeOut())
	{
		if (!refLevel->IsEnd(Vector2(position.x, position.y + 1)))
		{
			position.y += 1;
		}
		else {
			refLevel->DrawBlocks(position);
		}
		timer.Reset();
	}
}

void Blocks::Draw()
{
	SetColor(Color::White);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (block[j][i])
			{
				Engine::Get().SetCursorPosition(Vector2(prePosition.x + i, prePosition.y + j));
				Log(" ");
			}
		}
	}

	SetColor(color);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (block[j][i])
			{
				Engine::Get().SetCursorPosition(Vector2(position.x + i, position.y + j));
				Log("#");
			}
		}
	}

	// 색상 복구.
	SetColor(Color::White);
}
