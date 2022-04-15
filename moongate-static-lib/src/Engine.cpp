#include "moongate.h"
#include "World.h"
#include "Engine.h"
#include <iostream>

namespace moongate {
	Engine::Engine() {
		SDL_Log("Engine::()");
		_window = nullptr;
		_renderer = nullptr;
		_currentWorld = nullptr;
	}

	Engine::~Engine() {

	}

	int Engine::startup() {
		int result = 0;
		result = SDL_Init(SDL_INIT_EVERYTHING);
		if (result < 0) {
			SDL_Log("SDL_Init: %s", SDL_GetError());
			return -1;
		}

		_window = SDL_CreateWindow(
			"moongate",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			1024, 768,
			SDL_WINDOW_SHOWN
		);
		if (_window == NULL) {
			SDL_Log("SDL_CreateWindow: %s", SDL_GetError());
			return -2;
		}

		_renderer = SDL_CreateRenderer(
			_window,
			-1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (_renderer == NULL) {
			SDL_Log("SDL_CreateRenderer: %s", SDL_GetError());
			return -3;
		}

		return 1;
	}

	void Engine::shutdown() {
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		_renderer = nullptr;
		_window = nullptr;
		SDL_Quit();
	}

	void Engine::update() {
		bool quit  = false;
		SDL_Event event;
		while (!quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
					break;
				}
				if (event.type == SDL_KEYDOWN) {
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							quit = true;
						break;
					}
				}
			}

			if (_currentWorld != NULL) {
				_currentWorld->update();
			}

			SDL_SetRenderDrawColor(_renderer, 100, 149, 237, 235);
			SDL_RenderClear(_renderer);

			if (_currentWorld != NULL) {
				_currentWorld->render(_renderer);
			}

			SDL_RenderPresent(_renderer);

			SDL_Delay(100);
		}
	}

	int Engine::setCurrentWorld(World* newWorld) {
		if (_currentWorld != NULL) {
			_currentWorld->end();
		}

		_currentWorld = newWorld;
		_currentWorld->begin();

		return 1;
	}
}
