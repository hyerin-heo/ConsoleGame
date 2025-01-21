#include "Tetris1Level.h"
#include <Engine/Engine.h>
#include <Game/Game.h>
#include <Actor/Box.h>
#include <Actor/Blocks.h>
#include <Actor/Wall.h>

bool t1[3][3] = {
	{true, false, false},
	{true, false, false},
	{true, true, true}
};
bool t2[3][3] = {
	{false, false, true},
	{false, false, true},
	{true, true, true}
};
bool t3[3][3] = {
	{false, true, false},
	{false, true, false},
	{false, true, false}
};
bool t4[3][3] = {
	{true, true, true},
	{true, true, true},
	{true, true, true}
};
bool t5[3][3] = {
	{false, false, false},
	{false, false, false},
	{true, true, true}
};

const float level1Speed = 0.5f;
const int level1ClearScore = 300;

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
				Wall* wall = new Wall(Vector2(j, i));
				map.PushBack(wall);
				b2[i][j] = true;
			}
			else
			{
				if (j == 0 || j == x - 1)
				{
					Wall* wall = new Wall(Vector2(j, i));
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

#if _DEBUG
	/*bool testbuffer[15][20];
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			testbuffer[j][i] = mapList[j][i];
		}
	}*/
#endif // DEBUG

	Enter();
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
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		// 메뉴 토글.
		Game::Get().ToggleMenu();
	}

	if (isGameClear)
	{
		return;
	}
	Super::Update(deltaTime);
	if (!block)
	{
		//bool** b2 = new bool* [3];
		//for (int i = 0; i < 3; i++)
		//{
		//	b2[i] = new bool[3];
		//}

		////b2[0][0] = false;
		////b2[0][1] = false;
		////b2[0][2] = false;
		////b2[1][0] = false;
		////b2[1][1] = false;
		////b2[1][2] = false;

		//bool isAllFalse = false;
		//for (int i = 0; i < 3; i++)
		//{
		//	for (int j = 0; j < 3; j++)
		//	{
		//		b2[j][i] = Random(1, 10) % 2 == 0 ? true : false;
		//		isAllFalse = !b2[j][i] && !isAllFalse ? true : false;
		//	}
		//}

		//isAllFalse = true;
		//if (isAllFalse)
		//{
		//	b2[1][1] = true;
		//	b2[1][2] = true;
		//	b2[2][1] = true;
		//	b2[2][2] = true;
		//}

		block = new Blocks(GenerateBlock(), this, level1Speed);
	}

	block->Update(deltaTime);
}

void Tetris1Level::Draw()
{
	if (isGameClear)
	{
		return;
	}
	Super::Draw();
	if (block)
	{
		block->Draw();
	}
}

void Tetris1Level::Enter()
{
	for (auto* actor : map)
	{
		actor->Draw();
	}

	Engine::Get().SetCursorPosition(Vector2(Engine::Get().ScreenSize().x + 10, 2));
	Log("...Score...");
	PrintScore();
}

void Tetris1Level::DrawBlocks(const Vector2 position)
{
	bool** block = this->block->GetBlock();
	unsigned short color = this->block->GetColor();
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (block[y][x])
			{
				Box* box = new Box(Vector2(position.x + x, position.y + y), color);
				map.PushBack(box);
				mapList[position.y + y][position.x + x] = true;
			}
		}
	}

	delete this->block;
	this->block = nullptr;

	CheckScore();
}

bool Tetris1Level::IsEnd(const Vector2 position)
{
	bool** block = this->block->GetBlock();
	bool isEnd = false;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (block[y][x])
			{
				if (mapList[position.y + y][position.x + x])
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

Vector2 Tetris1Level::GetEndPosition(const Vector2 position)
{
	bool** block = this->block->GetBlock();
	for (int i = 1; i < Engine::Get().ScreenSize().y; i++)
	{
		if (IsEnd(Vector2(position.x, position.y + i)))
		{
			return Vector2(position.x, position.y + i - 1);
		}
	}
	return Vector2(0,0);
}

void Tetris1Level::CheckScore()
{
	List<int> removeIndex = {};
	//벽은 검사 안하기 위해
	for (int y = Engine::Get().ScreenSize().y - 2; y >= 1 ; --y)
	{
		bool isClear = true;
		for (int x = Engine::Get().ScreenSize().x - 1; x >= 1 ; --x)
		{
			isClear = mapList[y][x] && isClear;
		}
		if (isClear)
		{
			removeIndex.PushBack(y);
			// y라인의 줄의 액터를 모두 삭제
			
			for (DrawableActor* actor : map)
			{
				Box* eachBox = actor->As<Box>();
				if (eachBox && actor->Position().y == y)
				{
					int a = 3;
					// 색상을 모두 빨간색으로 바꾼 후
					eachBox->Crash();
				}
				// y라인보다 작은 라인의 블럭들 모두 y + 1로 땡김.
				if (eachBox && actor->Position().y < y)
				{
					eachBox->SetPosition(Vector2(actor->Position().x, actor->Position().y + 1));
				}
			}
		}
	}

	if (removeIndex.Size() > 0)
	{
		// map에서 삭제(delete, remove)
		for (int i = 0; i < map.Size();)
		{
			Box* box = map[i]->As<Box>();

			if (box && box->IsExpired())
			{
				delete map[i];
				map[i] = nullptr;
				map.Erase(i);
				continue;
			}
			++i;
		}

		// 맵리스트의 해당 위치 box position 변경.(한칸씩 땡김)
		for (int i = 0; i < removeIndex.Size(); i++)
		{
			for (int y = removeIndex[i]; y >= 2; y--)
			{
				for (int x = 1; x < Engine::Get().ScreenSize().x - 1; x++)
				{
					mapList[y][x] = mapList[y - 1][x];
				}
			}


			score += (100 * (i + 1));
		}
		PrintScore();

		// 0.5초후 삭제
		Sleep(500);
		//@TODO 더 좋은 방향으로 수정 할 것
		system("cls");
		Enter();
	}

	if (CheckGameClear())
	{
		GameClear();
	}
}

void Tetris1Level::GameClear()
{
	isGameClear = true;

	if (block)
	{
		delete block;
		block = nullptr;
	}

	ShowResult(true);
}

void Tetris1Level::GameOver()
{
	isGameClear = true;

	if (block)
	{
		delete block;
		block = nullptr;
	}

	ShowResult(false);
}

bool** Tetris1Level::GenerateBlock()
{
	bool** temp = new bool* [3];
	for (int i = 0; i < 3; i++)
	{
		temp[i] = new bool[3];
	}

	int random = Random(1, 5);

	switch (random)
	{
	case 1:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				temp[j][i] = t1[j][i];
			}
		}
		break;
	case 2:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				temp[j][i] = t2[j][i];
			}
		}
		break;
	case 3:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				temp[j][i] = t3[j][i];
			}
		}
		break;
	case 4:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				temp[j][i] = t4[j][i];
			}
		}
		break;
	default:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				temp[j][i] = t5[j][i];
			}
		}
		break;
	}
	return temp;
}

bool Tetris1Level::CheckGameClear()
{
	return score >= level1ClearScore;
}

void Tetris1Level::PrintScore()
{
	Engine::Get().SetCursorPosition(Vector2(Engine::Get().ScreenSize().x + 10, 3));
	std::cout << score;
}

void Tetris1Level::ShowResult(bool isClear)
{
	int x = Engine::Get().ScreenSize().x;
	int y = Engine::Get().ScreenSize().y;

	int startY = y * 0.5f - 3;
	int endY = startY + 3;
	if (isClear)
	{
		SetColor(Color::Yellow);
	}
	else {
		SetColor(Color::Red);
	}

	for (int i = startY; i < endY; i++)
	{
		for (int j = 0; j < x; j++)
		{
			Engine::Get().SetCursorPosition(j, i);
			if (i == startY || i == endY - 1)
			{
				Log("-");
			}
			else if (j == 0 || j == x - 1)
			{
				Log("|");
			}
			else 
			{
				Log(" ");
			}
		}
	}

	Engine::Get().SetCursorPosition((x * 0.5f) - 5, y * 0.5f);
	if (isClear)
	{
		Log("GAME CLEAR!!");
	}
	else {
		Log("YOU DIED!!");
	}
	SetColor(Color::White);

	//@TODO 몇 초 후 메뉴로 돌아가기.
}
