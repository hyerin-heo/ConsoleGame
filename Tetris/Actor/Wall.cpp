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
