#pragma once

#include <Actor/Actor.h>

class Tetris1Level;
class Blocks : public Actor
{
	RTTI_DECLARATIONS(Blocks, Actor)
public:
	Blocks(bool** block, Tetris1Level* refLevel, float speed);
	~Blocks();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	bool** GetBlock() const { return block; }
	unsigned short GetColor() const { return color; }

private:
	Vector2 prePosition;
	Tetris1Level* refLevel = nullptr;
	bool** block;
	unsigned short color;

	bool isDone = false;

	float speed = 0.5f;
};