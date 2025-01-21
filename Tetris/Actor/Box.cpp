#include "Box.h"
#include <Engine/Engine.h>

Box::Box(const Vector2& position, unsigned short color)
	: DrawableActor("#")
{
	this->position = position;
	this->intColor = color;
	this->color = Color::Red;
}

void Box::Draw()
{
	SetColor(intColor);

	Engine::Get().SetCursorPosition(position);

	Log(image);

	SetColor(Color::White);
}

void Box::Crash()
{
	// 색상 설정.
	SetColor(color);

	Engine::Get().SetCursorPosition(position);

	Log("^");

	// 색상 복구.
	SetColor(Color::White);

	isExpired = true;
}
