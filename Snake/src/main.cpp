
#include "moongate.h"
#include <iostream>

class SnakeEngine : public moongate::Engine {
	public:
		SnakeEngine() : Engine() {}
		~SnakeEngine() = default;
};


int main(int argc, char* argv[]) {
	SnakeEngine* engine = new SnakeEngine();
	int result = 0;
	if (engine->startup() < 0) {
		goto CLEANUP_AND_QUIT;
	}

	engine->update();

CLEANUP_AND_QUIT:
	engine->shutdown();

	delete engine;
	return 0;
}