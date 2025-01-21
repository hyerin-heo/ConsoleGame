#include "Game.h"

#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game(const Vector2& screenSize)
	: Engine(screenSize)
{
	instance = this;

	menuLevel = new MenuLevel();

}

Game::~Game()
{
	if (showMenu)
	{
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		delete mainLevel;
		mainLevel = nullptr;
	}

	delete menuLevel;
	menuLevel = nullptr;
}

void Game::ToggleMenu()
{
	system("cls");
	//Clear();
	showMenu = !showMenu;
	if (showMenu)
	{
		backLevel = mainLevel;
		mainLevel = menuLevel;
	}
	else
	{
		mainLevel = backLevel;
	}

	ReDrawGame();
}

void Game::ReDrawGame()
{
	if (mainLevel != menuLevel)
	{
		mainLevel->Enter();
	}
}
