#include "Wall.h"
#include <Engine/Engine.h>

Wall::Wall(const Vector2& position)
	: DrawableActor("@")
{
	// 위치 설정.
	this->position = position;

	// 색상 설정.
	color = Color::Green;
}

void Wall::Draw()
{
	//Super::Draw();

	// 색상 설정.
	SetColor(color);

	Engine::Get().SetCursorPosition(position);

	Log(image);

	// 색상 복구.
	SetColor(Color::White);

	//std::cout << "position : (" << position.x << ", " << position.y << ")\n";
}
