#pragma once
#include "Actor/DrawableActor.h"

class Space : public DrawableActor 
{
	RTTI_DECLARATIONS(Space, DrawableActor)
public:
	Space(const Vector2& position);
	~Space();

private:

};