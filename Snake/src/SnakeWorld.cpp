#include "SnakeWorld.h"

SnakeWorld::SnakeWorld() : World() {
    _x = 200;
    _y = 200;
}

void SnakeWorld::begin() {
	SDL_Log("SnakeWorld::begin");
    World::begin();
}

void SnakeWorld::end() {
	SDL_Log("SnakeWorld::end");
    World::end();
}

void SnakeWorld::update(std::deque<SDL_Event> queue) {
    
    for (SDL_Event key_event : queue) {
        switch (key_event.key.keysym.sym) {
            case SDLK_UP:
                _y = _y - 5;
            break;
            case SDLK_DOWN:
                _y = _y + 5;
            break;
            case SDLK_LEFT:
                _x = _x - 5;
            break;
            case SDLK_RIGHT:
                _x = _x + 5;
            break;
        }
    }
    

}

void SnakeWorld::render(SDL_Renderer* renderer) {

    SDL_Rect rect {_x, _y, 200, 200};
    /*rect.x = 250;
    rect.y = 150;
    rect.w = 200;
    rect.h = 200;*/

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

}
