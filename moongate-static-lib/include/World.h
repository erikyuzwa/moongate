#ifndef __WORLD_H_
#define __WORLD_H_

namespace moongate {
	class World {
		public:
			World();
			virtual ~World() = default;

			virtual void begin() = 0;
			virtual void end() = 0;

			virtual void update();
			virtual void render(SDL_Renderer* renderer);
	};
}

#endif