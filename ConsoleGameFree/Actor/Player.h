#pragma once

#include <Actor/DrawableActor.h>

class Timer;
class GameLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const Vector2& position, GameLevel* level);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	int GetBoostCount() const { return boostCount; }
	void ResetBoostCount() { boostCount = 0; }
private:
	GameLevel* refLevel = nullptr;

	Vector2 prePosition;

	//���߿� �ִ��� �ƴ���.
	bool onSpace = false;

	int boostCount = 0;
};