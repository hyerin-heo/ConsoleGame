#include "Box.h"
#include <Engine/Engine.h>

Box::Box(const Vector2& position, unsigned short color)
	: DrawableActor("@")
{
	this->position = position;
	this->intColor = color;
}

void Box::Draw()
{
	Super::Draw();

	// 색상 설정.
	SetColor(intColor);

	Engine::Get().SetCursorPosition(position);

	Log(image);

	// 색상 복구.
	SetColor(Color::White);
}