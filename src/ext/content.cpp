#include "ext/content.h"

#include <iostream>

namespace content {

ContentBase::~ContentBase() { }

const string StringContent::default_font = "fonts/arial.ttf";

StringContent::StringContent(const StringContent& origin)
    : value(origin.value), color(origin.color),
      font(origin.font), size(origin.size) { reload_ttf(); }

StringContent::~StringContent() {
    gtf.freeFont(font);
}

pair<int, int> StringContent::get_size() {
    int w, h;
    TTF_SizeUTF8(this->_ttf, this->value.data(), &w, &h);
    
    return {w, h};
}

void StringContent::render(const components::ComponentBase* comp, SDL_Renderer* rd) {
    SDL_Surface* sf = TTF_RenderUTF8_Blended(_ttf, this->value.c_str(), comp->get_foreground().color());
    
    if (sf == nullptr) {
        cout << "SDL : " << TTF_GetError()
             << "\nComponent ID / Name : " << comp->uid << " / " << comp->name();
        exit(-1);
    }
    
    SDL_Texture* tx = SDL_CreateTextureFromSurface(rd, sf);
    
    if (tx == nullptr) {
        cout << "SDL : " << TTF_GetError()
             << "\nComponent ID / Name : " << comp->uid << " / " << comp->name();
        exit(-1);
    }
    
    Point p = 
        this->get_margin().map(
            Point { comp->get_width(), comp->get_height() },
            Point { (float)sf->w, (float)sf->h },
            this->get_horizontal(),
            this->get_vertical()
        );
    SDL_Rect r { (int)p.x, (int)p.y, sf->w, sf->h };
    SDL_FreeSurface(sf);
    
    SDL_RenderCopy(rd, tx, nullptr, &r);
    SDL_DestroyTexture(tx);
    
    /*
    Point p = 
        this->margin.map(
            Point {
                comp->get_width(),
                comp->get_height()
            },
            // Point { this->margin.vertical, this->margin.horizontal },
            this->horizontal,
            this->vertical
        );
   
    stringRGBA(
        rd, p.x, p.y, this->value.c_str(),
        this->color.R(), this->color.G(), this->color.B(), this->color.A()
    );
    */
    
}

void StringContent::init() {
    /*
    ttf = TTF_OpenFont(this->font.c_str(), this->size);
    
    if (ttf == nullptr) {
        cout << "\nSDL : " << TTF_GetError();
        exit(-1);
    }
    */
}

}