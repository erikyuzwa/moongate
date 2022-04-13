#include "SnakeWorld.h"

SnakeWorld::SnakeWorld() : World() {

}

void SnakeWorld::begin() {
	SDL_Log("begin");
}

void SnakeWorld::end() {
	SDL_Log("end");
}

void SnakeWorld::update() {

}

void SnakeWorld::render(SDL_Renderer* renderer) {

    SDL_Rect rect {250, 150, 200, 200};
    /*rect.x = 250;
    rect.y = 150;
    rect.w = 200;
    rect.h = 200;*/

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

}
