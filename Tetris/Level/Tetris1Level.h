#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>

class DrawableActor;
class Blocks;
class Tetris1Level : public Level
{
	RTTI_DECLARATIONS(Tetris1Level, Level)

public:
	Tetris1Level();
	~Tetris1Level();

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;

	virtual void Enter() override;

	void DrawBlocks(const Vector2 position);

	bool IsEnd(const Vector2 position);

	void CheckScore();

	void GameClear();
	void GameOver();

	bool** GenerateBlock();
private:
	bool CheckGameClear();

	void PrintScore();

	void ShowResult(bool isClear);

private:
	List<DrawableActor*> map;
	bool** mapList;

	Blocks* block = nullptr;

	bool isGameClear = false;

	int score = 0;
};