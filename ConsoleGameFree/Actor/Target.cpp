#include "Target.h"

Target::Target(const Vector2& position)
	: DrawableActor("P")
{
	// 위치 설정.
	this->position = position;

	// 색상 설정.
	color = Color::Blue;
}