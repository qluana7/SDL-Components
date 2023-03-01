#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "components/component.h"
#include "components/label.h"

#ifdef _WIN32
#define DEFAULT_FONT "C:\\Windows\\Fonts\\arial.ttf"
#elif __linux__
#define DEFAULT_FONT "'PLEASE INPUT FONT LOCATION'"
#endif

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
    
    components::Label hlbael(
        100, 40, align::Margin(-50, -20),
        align::HorizontalAlign::MIDDLE,
        align::VerticalAlign::MIDDLE
    );
    
    content::StringContent hstr;
    hstr.set_horizontal(align::HorizontalAlign::MIDDLE);
    hstr.set_vertical(align::VerticalAlign::MIDDLE);
    hstr.set_font(DEFAULT_FONT, 13);
    hstr.set_value("Hello, World!");
    hlbael.set_content(hstr);
    
    mgr.add_component(&hlbael);

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