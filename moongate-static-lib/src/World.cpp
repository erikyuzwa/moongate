#include "moongate.h"
#include "World.h"

namespace moongate {
	World::World() {

	}

	void World::begin() {
		SDL_Log("World::begin");
	}

	void World::end() {
		SDL_Log("World::end");
	}

	void World::update(std::deque<SDL_Event> queue) {

	}

	void World::render(SDL_Renderer* renderer) {

	}
}
