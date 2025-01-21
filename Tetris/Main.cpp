#include <iostream>
#include <Game/Game.h>
#include "Level/Tetris1Level.h"

int main() 
{
	CheckMemoryLeak();

	Game game(Vector2(20, 15));
	game.LoadLevel(new Tetris1Level());
	game.Run();
}