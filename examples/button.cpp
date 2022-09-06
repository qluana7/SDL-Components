#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "components/component.h"
#include "components/button.h"
#include "components/label.h"

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

void btn1_leave(Object& sender, event::MouseEventArgs e) {
    auto& btn = sender.cast<components::Button>();
    btn.set_background(0xcfcfcfff);
}

void btn1_mouse_down(Object& sender, event::MouseEventArgs e) {
    auto& btn = sender.cast<components::Button>();
    btn.set_background(0x7f7f7fff);
}

void btn1_mouse_up(Object& sender, event::MouseEventArgs e) {
    auto& btn = sender.cast<components::Button>();
    btn.set_background(0xcfcfcfff);
}

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
    
    components::Button btn1(
        100, 40, align::Margin(-50, -20),
        align::HorizontalAlign::MIDDLE,
        align::VerticalAlign::MIDDLE
    );

    btn1.mouse_down_event += btn1_mouse_down;
    btn1.mouse_up_event += btn1_mouse_up;
    btn1.leave_event += btn1_leave;
    mgr.add_component(&btn1);
    
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