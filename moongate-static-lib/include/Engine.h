#ifndef __ENGINE_H_
#define __ENGINE_H_

namespace moongate {
	class Engine {
		protected:
			SDL_Window* _window;
			SDL_Renderer* _renderer;
		public:
			Engine();
			virtual ~Engine();

			int startup();
			void update();
			void shutdown();
	};
}

#endif
