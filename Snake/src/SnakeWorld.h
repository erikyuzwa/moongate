#ifndef __SNAKEWORLD_H_
#define __SNAKEWORLD_H_

#include "moongate.h"

class SnakeWorld : public moongate::World {
	private:
		int _x;
		int _y;

	public:
		SnakeWorld();
		~SnakeWorld() = default;

		void begin();
		void end();
		void update(std::deque<SDL_Event> queue);
		void render(SDL_Renderer* renderer);
};

#endif
