#include "core.h"
#include <iostream>
#include "Game.h"


Game game;



bool Update(float dt) {
	bool quit = game.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics){
	game.Draw(graphics);
}

int main() {
	game.Startup();

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	game.Shutdown();
	Core::Shutdown();
}