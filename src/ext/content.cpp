#include "ext/content.h"

#include <iostream>

namespace content {

ContentBase::~ContentBase() { }

StringContent::~StringContent() {
    // TTF_CloseFont(ttf);
}

void StringContent::render(const components::ComponentBase* comp, SDL_Renderer* rd) {
    
    /*
    SDL_Surface* sf = TTF_RenderUTF8_Blended(ttf, this->value.c_str(), comp->_foregd.color());
    
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
        this->margin.map(
            Point { comp->_width, comp->_height },
            Point { (float)sf->w, (float)sf->h },
            this->horizontal,
            this->vertical
        );
    SDL_Rect r { (int)p.x, (int)p.y, sf->w, sf->h };
    SDL_FreeSurface(sf);
    
    SDL_RenderCopy(rd, tx, nullptr, &r);
    SDL_DestroyTexture(tx);
    */
    
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
    
}

void StringContent::init() {
    /*
    ttf = TTF_OpenFont(this->ttf_location.c_str(), this->pt);
    
    if (ttf == nullptr) {
        cout << "\nSDL : " << TTF_GetError();
        exit(-1);
    }
    */
}

}