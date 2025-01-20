#include "Tetris1Level.h"
#include <Engine/Engine.h>
#include <Actor/Box.h>
#include <Actor/Blocks.h>
#include <Actor/Wall.h>

bool b1[3][3] =
{
	{false, true, false},
	{true, true, true },
	{true, false, true }
};

Tetris1Level::Tetris1Level()
{
	Engine::Get().SetCursorType(CursorType::NoCursor);
	const int x = Engine::Get().ScreenSize().x;
	const int y = Engine::Get().ScreenSize().y;

	bool** b2 = new bool* [y];
	for (int i = 0; i < x; i++)
	{
		b2[i] = new bool[x];
	}
	//mapList = new bool[x][y];
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (i == 0 || i == x - 1)
			{
				Wall* wall = new Wall(Vector2(i, j));
				map.PushBack(wall);
				b2[i][j] = true;
			}
			else
			{
				if (j == 0 || j == y - 1)
				{
					Wall* wall = new Wall(Vector2(i, j));
					map.PushBack(wall);
					b2[i][j] = true;
				}
				else 
				{
					b2[i][j] = false;
				}
			}
		}
	}

	mapList = b2;


	for (auto* actor : map)
	{
		actor->Draw();
	}
}

Tetris1Level::~Tetris1Level()
{
}

void Tetris1Level::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (!block)
	{
		bool** b2 = new bool* [3];
		for (int i = 0; i < 3; i++)
		{
			b2[i] = new bool[3];
		}

		bool isAllFalse = false;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				b2[i][j] = Random(1, 10) % 2 == 0 ? true : false;
				isAllFalse = !b2[i][j] && !isAllFalse ? true : false;
			}
		}

		if (isAllFalse)
		{
			b2[1][1] = true;
			b2[1][2] = true;
			b2[2][1] = true;
			b2[2][2] = true;
		}

		block = new Blocks(b2, this, 0.5f);
	}

	block->Update(deltaTime);
}

void Tetris1Level::Draw()
{
	Super::Draw();
	if (block)
	{
		block->Draw();
	}
}

void Tetris1Level::DrawBlocks(const Vector2 position)
{
	bool** block = this->block->GetBlock();
	unsigned short color = this->block->GetColor();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (block[i][j])
			{
				Box* box = new Box(Vector2(position.x + i, position.y + j), color);
				map.PushBack(box);
				mapList[position.x + i][position.y + j] = true;
				this->block = nullptr;
			}
		}
	}
}

bool Tetris1Level::IsEnd(const Vector2 position)
{
	bool** block = this->block->GetBlock();
	bool isEnd = false;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (block[i][j])
			{
				if (mapList[position.x + i][position.y + j])
				{
					isEnd = true;
					break;
				}
			}
		}
		if (isEnd)
		{
			break;
		}
	}
	return isEnd;
}

bool Tetris1Level::CheckGameClear()
{
	return false;
}
