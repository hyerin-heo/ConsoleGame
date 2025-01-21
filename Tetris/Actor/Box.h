#pragma once

#include <Actor/DrawableActor.h>

class Box : public DrawableActor
{
	RTTI_DECLARATIONS(Box, DrawableActor)

public:
	Box(const Vector2& position, unsigned short color);

	virtual void Draw() override;

	void Crash();

	bool IsExpired() { return isExpired; }

private:
	unsigned short intColor;
};