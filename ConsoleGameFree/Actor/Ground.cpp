#include "Ground.h"

Ground::Ground(const Vector2& position)
	: DrawableActor("_")
{
	// ��ġ ����.
	this->position = position;

	// ���� ����.
	color = Color::Red;
}