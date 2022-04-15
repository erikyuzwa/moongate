#include <iostream>
#include "SnakeEngine.h"
#include "SnakeWorld.h"


int main(int argc, char* argv[]) {
	SnakeEngine* engine = new SnakeEngine();
	int result = 0;
	if (engine->startup() < 0) {
		goto CLEANUP_AND_QUIT;
	}

	engine->setCurrentWorld(new SnakeWorld());

	engine->update();

CLEANUP_AND_QUIT:
	engine->shutdown();

	delete engine;
	return 0;
}