#include "GameLevel.h"
#include "Engine/Engine.h"

#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Space.h"
#include "Actor/Target.h"
#include "Actor/Player.h"

#include "Engine/Timer.h"

GameLevel::GameLevel()
{
	// 커서 감추기.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	// 맵 파일 불러와 레벨 로드.
	// 파일 읽기.
	FILE* file = nullptr;
	//fopen_s(&file, "../Assets/Maps/Map.txt", "rb");
	fopen_s(&file, "../Assets/Maps/Stage1.txt", "rb");

	// 파일 처리.
	if (file == nullptr)
	{
		std::cout << "맵 파일 열기 실패.\n";
		__debugbreak();
		return;
	}

	// 파일 읽기.
	// 끝위치로 이동.
	fseek(file, 0, SEEK_END);

	// 이동한 위치의 FP 가져오기.
	size_t readSize = ftell(file);

	// FP 원위치.
	//fseek(file, 0, SEEK_SET);
	rewind(file);

	// 파일 읽어서 버퍼에 담기.
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "읽어온 크기가 다름\n";
		__debugbreak();
		return;
	}

	buffer[readSize] = '\0';

	// 파일 읽을 때 사용할 인덱스.
	int index = 0;

	// 좌표 계산을 위한 변수 선언.
	int xPosition = 0;
	int yPosition = 0;

	// 해석 (파싱-Parcing).
	while (index < (int)bytesRead)
	{
		// 한 문자씩 읽기.
		char mapChar = buffer[index++];

		// 개행 문자인 경우 처리.
		if (mapChar == '\n')
		{
			++yPosition;
			xPosition = 0;
			continue;
		}

		if (mapChar == '1')
		{
			Wall* wall = new Wall(Vector2(xPosition, yPosition));
			actors.PushBack(wall);
			map.PushBack(wall);
		}

		// 맵 문자가 _이면 그라운드 액터 생성.
		else if (mapChar == '-')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);
		}

		else if (mapChar == '.')
		{
			Space* space = new Space(Vector2(xPosition, yPosition));
			actors.PushBack(space);
			map.PushBack(space);
		}

		else if (mapChar == 'P')
		{
			Target* target = new Target(Vector2(xPosition, yPosition));
			actors.PushBack(target);
			map.PushBack(target);
			this->target = target;
		}

		else if (mapChar == 'p')
		{
			player = new Player(
				Vector2(xPosition, yPosition),
				this
			);
			actors.PushBack(player);
		}

		++xPosition;
	}

	// 버퍼 삭제.
	delete[] buffer;

	// 파일 닫기.
	fclose(file);
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (isGameClear)
	{
		// 타이머.
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		// 커서 이동.
		Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y + 2);

		// 메시지 출력.
		Log("Game Clear! Find Princess!");

		// 쓰레드 정지.
		Sleep(2000);

		// 게임 종료 처리.
		Engine::Get().QuitGame();
	}

	if (true)
	{
		Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y);

		Log("Super Jump...");
		Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y + 1);
		int c = player->GetBoostCount();
		char txt[] = "|||||";//▮
		for (int i = 0; i < c; i++)
		{
			txt[i] = '0';
		}
		Log(" (%s) ", txt );
	}
}

void GameLevel::Draw()
{
	// 맵 그리기.
	for (auto* actor : map)
	{
		// 플레이어 위치 확인.
		if (actor->Position() == player->Position())
		{
			continue;
		}

		actor->Draw();
	}

	target->Draw();

	// 플레이어 그리기.
	player->Draw();
}

bool GameLevel::CanPlayerMove(const Vector2& position)
{
	// 게임이 클리어된 경우 바로 종료.
	if (isGameClear)
	{
		return false;
	}

	DrawableActor* searchedActor = nullptr;
	Vector2 tempPos = Vector2(position.x, position.y + 1);//발 밑에 땅이 있는지 확인하기 위함.
	for (auto* actor : map)
	{
		if (actor->Position() == tempPos)
		{
			searchedActor = actor;
			break;
		}
	}


	if (!searchedActor)
	{
		return false;
	}

	if (searchedActor->As<Ground>()
		|| searchedActor->As<Target>()
		|| searchedActor->As<Space>())
	{
		return true;
	}

	return false;
}

bool GameLevel::CanJump(const Vector2& position)
{
	if (isGameClear)
	{
		return false;
	}

	DrawableActor* searchedActor = nullptr;
	Vector2 tempPos = Vector2(position.x, position.y + 1);//내 위에 그라운드가 있는지 확인하기 위함.
	for (auto* actor : map)
	{
		if (actor->Position() == tempPos)
		{
			searchedActor = actor;
			break;
		}
	}

	if (searchedActor)
	{
		//내 위에 땅이 있으면 못움직임.
		if (searchedActor->As<Ground>() || 
			searchedActor->As<Wall>())
		{
			return false;
		}
	}

	return true;
}

bool GameLevel::OnSpace(const Vector2& position)
{
	// 게임이 클리어된 경우 바로 종료.
	if (isGameClear)
	{
		return false;
	}

	DrawableActor* searchedActor = nullptr;

	Vector2 tempPos = Vector2(position.x, position.y + 1);
	for (auto* actor : map)
	{
		if (actor->Position() == tempPos)
		{
			searchedActor = actor;
			break;
		}
	}

	if (!searchedActor)
	{
		return false;
	}

	if (searchedActor->As<Space>())
	{
		return true;
	}

	return false;
}

bool GameLevel::CheckGameClear()
{
	if (player->Position() == target->Position())
	{
		return true;
	}

	return false;
}