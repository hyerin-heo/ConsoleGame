#include "Target.h"

Target::Target(const Vector2& position)
	: DrawableActor("P")
{
	// ��ġ ����.
	this->position = position;

	// ���� ����.
	color = Color::Blue;
}