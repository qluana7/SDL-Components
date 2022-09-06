#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "components/component.h"
#include "components/button.h"

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

int selector = 0;
const int MAXTAB = 1;

void btn_leave(Object& sender, event::MouseEventArgs e) {
    auto& btn = sender.cast<components::Button>();
    btn.set_background(0xcfcfcfff);
}

void next_mouse_down(Object& sender, event::MouseEventArgs e) {
    auto& btn = sender.cast<components::Button>();
    btn.set_background(0x7f7f7fff);
    if (selector == MAXTAB) selector = 0;
    else selector++;
}

void btn_mouse_down(Object& sender, event::MouseEventArgs e) {
    auto& btn = sender.cast<components::Button>();
    btn.set_background(0x7f7f7fff);
}

void btn_mouse_up(Object& sender, event::MouseEventArgs e) {
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
    
    components::ComponentManager main(win), tab1(win), tab2(win);
    
    components::Button next(
        30, 30, align::Margin(-50, -50),
        align::HorizontalAlign::RIGHT,
        align::VerticalAlign::BOTTOM
    );
    
    next.mouse_down_event += next_mouse_down;
    next.mouse_up_event += btn_mouse_up;
    next.leave_event += btn_leave;
    main.add_component(&next);
    
    components::Button btn1(
        100, 40, align::Margin(-50, -20),
        align::HorizontalAlign::MIDDLE,
        align::VerticalAlign::MIDDLE
    );

    btn1.mouse_down_event += btn_mouse_down;
    btn1.mouse_up_event += btn_mouse_up;
    btn1.leave_event += btn_leave;
    tab1.add_component(&btn1);
    
    components::Button btn2(
        40, 100, align::Margin(-40, -50),
        align::HorizontalAlign::MIDDLE,
        align::VerticalAlign::MIDDLE
    );
    btn2.mouse_down_event += btn_mouse_down;
    btn2.mouse_up_event += btn_mouse_up;
    btn2.leave_event += btn_leave;
    tab2.add_component(&btn2);
    
    components::Button btn3(
        40, 100, align::Margin(0, -50),
        align::HorizontalAlign::MIDDLE,
        align::VerticalAlign::MIDDLE
    );
    btn3.mouse_down_event += btn_mouse_down;
    btn3.mouse_up_event += btn_mouse_up;
    btn3.leave_event += btn_leave;
    tab2.add_component(&btn3);
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    while (true) {
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(renderer);
        
        main.render(renderer);
        switch (selector) {
            case 0: tab1.render(renderer); break;
            case 1: tab2.render(renderer); break;
        }
        
        SDL_RenderPresent(renderer);
        
        SDL_WaitEventTimeout(&event, 10);
        
        if (event.type == SDL_QUIT) break;
    }
    
    tab1.clear();
    tab2.clear();
    
    deinit();
    
    return 0;
}