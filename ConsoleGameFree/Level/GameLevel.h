#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>

// 소코반 게임 레벨.
class DrawableActor;
class Player;
class Box;
class Target;
class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;

	bool CanPlayerMove(const Vector2& position);
	bool CanJump(const Vector2& position);

	bool OnSpace(const Vector2& position);

private:
	bool CheckGameClear();

private:
	List<char*> mapStr;
	List<DrawableActor*> map;

	Target* target;

	Player* player = nullptr;

	bool isGameClear = false;
};