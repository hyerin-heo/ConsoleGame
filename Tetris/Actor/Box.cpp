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
	// ���� ����.
	SetColor(color);

	Engine::Get().SetCursorPosition(position);

	Log("^");

	// ���� ����.
	SetColor(Color::White);

	isExpired = true;
}
