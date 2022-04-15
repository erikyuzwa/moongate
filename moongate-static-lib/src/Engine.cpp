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
		std::deque<SDL_Event> queue_keys;
		while (!quit) {
			queue_keys.clear();

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
						case SDLK_F1:
							SDL_Log("Engine::toggleFullscreen");
							toggleFullscreen();
						break;
						case SDLK_F2:
							SDL_Log("Engine::captureScreenshot");
							captureScreenshot();
						break;
						default:
							queue_keys.push_back(event);
						break;
					}
				}
			}

			if (_currentWorld != NULL) {
				_currentWorld->update(queue_keys);
			}

			//SDL_SetRenderDrawColor(_renderer, 100, 149, 237, 235);
			SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
			SDL_RenderClear(_renderer);

			if (_currentWorld != NULL) {
				_currentWorld->render(_renderer);
			}

			SDL_RenderPresent(_renderer);

			SDL_Delay(100);
		}
	}

	void Engine::captureScreenshot() {
		int w = 0;
		int h = 0;
		SDL_GetRendererOutputSize(_renderer, &w, &h);
		
		time_t rawtime;
		struct tm timeinfo;
		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		char buffer[80];
		strftime(buffer, 80, "screenshot-%Y-%m-%d_%H-%M-%S.bmp", &timeinfo);

		SDL_Surface* sshot = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		SDL_RenderReadPixels(_renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
		SDL_SaveBMP(sshot, buffer);
		SDL_FreeSurface(sshot);
	}


	void Engine::toggleFullscreen() {
		int flags = SDL_GetWindowFlags(_window);
		int isFullscreen = (flags & SDL_WINDOW_FULLSCREEN) ? true : false;
		
		SDL_SetWindowFullscreen(_window, !isFullscreen);
		SDL_SetWindowInputFocus(_window);
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
