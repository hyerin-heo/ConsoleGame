#pragma once

#include <Engine/Engine.h>

class Game : public Engine
{
public:
	Game(const Vector2& screenSize = Vector2(40,25));
	~Game();

	void ToggleMenu();

	void ReDrawGame();

	static Game& Get() { return *instance; }

private:
	bool showMenu = false;

	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

private:
	static Game* instance;
};