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

	// 2차원 배열에서 앞 인덱스가 y 두번째가 x.
	bool** b2 = new bool*[y];
	for (int i = 0; i < y; i++)
	{
		b2[i] = new bool[x];
	}
	
	//mapList = new bool[y][x];
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (i == 0 || i == y - 1)
			{
				Wall* wall = new Wall(Vector2(i, j));
				map.PushBack(wall);
				b2[i][j] = true;
			}
			else
			{
				if (j == 0 || j == x - 1)
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
	if (block)
	{
		delete block;
	}

	if (map.Size() > 0)
	{
		for (auto* actor : map)
		{
			delete actor;
		}
	}

	if (mapList != nullptr)
	{
		for (int y = 0; y < Engine::Get().ScreenSize().y; ++y)
		{
			if (mapList[y])
			{
				delete[] mapList[y];
			}
		}

		delete mapList;
	}
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
				b2[j][i] = Random(1, 10) % 2 == 0 ? true : false;
				isAllFalse = !b2[j][i] && !isAllFalse ? true : false;
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
