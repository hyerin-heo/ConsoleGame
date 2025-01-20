#include <iostream>
#include <Game/Game.h>
#include "Level/Tetris1Level.h"

int main() 
{
	Game game;
	game.LoadLevel(new Tetris1Level());
	game.Run();
}