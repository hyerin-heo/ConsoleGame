#include "Wall.h"
#include <Engine/Engine.h>

Wall::Wall(const Vector2& position)
	: DrawableActor("@")
{
	// ��ġ ����.
	this->position = position;

	// ���� ����.
	color = Color::Green;
}

void Wall::Draw()
{
	//Super::Draw();

	// ���� ����.
	SetColor(color);

	Engine::Get().SetCursorPosition(position);

	Log(image);

	// ���� ����.
	SetColor(Color::White);

	//std::cout << "position : (" << position.x << ", " << position.y << ")\n";
}
