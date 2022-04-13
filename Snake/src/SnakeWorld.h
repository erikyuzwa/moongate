#ifndef __SNAKEWORLD_H_
#define __SNAKEWORLD_H_

#include "moongate.h"

class SnakeWorld : public moongate::World {
	public:
		SnakeWorld();
		~SnakeWorld() = default;

		void begin();
		void end();
		void update();
		void render(SDL_Renderer* renderer);
};

#endif
