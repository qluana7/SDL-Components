#pragma once

#include <string>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "ext/align.h"
#include "components/component.h"

namespace content {

struct ContentBase {
    ContentBase() : horizontal(align::HorizontalAlign::LEFT), vertical(align::VerticalAlign::TOP) { }
    ContentBase(const ContentBase&) = default;
    virtual ~ContentBase() = 0;
    
    align::HorizontalAlign horizontal;
    align::VerticalAlign vertical;
    
    align::Margin margin;
    
    virtual void render(const components::ComponentBase* comp, SDL_Renderer* rd) = 0;
    
    virtual void init() = 0;
};

struct StringContent : ContentBase {
    StringContent() = default;
    StringContent(const StringContent&) = default;
    virtual ~StringContent() final;
    
    std::string value;
    color::RGBA color = (unsigned int)0x0;
    
    std::string ttf_location;
    int pt;
    
    virtual void render(const components::ComponentBase* comp, SDL_Renderer* rd) final;
    
    void init();

private:
    // TTF_Font* ttf;
};

}