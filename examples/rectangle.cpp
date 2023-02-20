#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "components/component.h"
#include "components/rectangle.h"

using namespace std;

SDL_Window* win;
SDL_Renderer* renderer;

void deinit() {
    if (renderer != nullptr) { SDL_DestroyRenderer(renderer); }
    if (win      != nullptr) { SDL_DestroyWindow(win); }
    SDL_Quit();
}

#define WIN_WIDTH  300
#define WIN_HEIGHT 150

int main(int argc, char ** argv) {
    SDL_Init(SDL_INIT_VIDEO);
    
    win = SDL_CreateWindow(
		"Example",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIN_WIDTH, WIN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

    renderer = SDL_CreateRenderer(
		win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE
	);
    
    SDL_Event event;
    
    components::ComponentManager mgr(win);
    
    components::Rectangle red(
        {0, 0}, 100, 150, 0xff0000ff, 0x0
    );
    components::Rectangle green(
        {100, 0}, 100, 150, 0x00ff00ff, 0x0 
    );
    components::Rectangle blue(
        {200, 0}, 100, 150, 0x0000ffff, 0x0 
    );

    components::Rectangle mid(
        {30, 50}, 240, 50, 0x0, 0x000000ff
    ); mid.set_radius(8);
    
    mgr.add_component(&red);
    mgr.add_component(&green);
    mgr.add_component(&blue);
    
    mgr.add_component(&mid);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    while (true) {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        
        mgr.render(renderer);
        
        SDL_RenderPresent(renderer);
        
        SDL_WaitEventTimeout(&event, 10);
        
        if (event.type == SDL_QUIT) break;
    }
    
    mgr.clear();
    
    deinit();
    
    return 0;
}