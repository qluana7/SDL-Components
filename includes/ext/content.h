#pragma once

#include <string>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "ext/align.h"
#include "ext/ttf.h"
#include "components/component.h"

using namespace std;

namespace content {

struct ContentBase {
    ContentBase() : horizontal(align::HorizontalAlign::LEFT), vertical(align::VerticalAlign::TOP) { }
    ContentBase(const ContentBase&) = default;
    virtual ~ContentBase() = 0;

private:
    align::HorizontalAlign horizontal;
    align::VerticalAlign vertical;
    
    align::Margin margin;
    
public:
    align::HorizontalAlign get_horizontal() const { return horizontal; }
    align::VerticalAlign   get_vertical  () const { return vertical;   }
    align::Margin          get_margin    () const { return margin;     }
    
    void set_horizontal(align::HorizontalAlign h) { horizontal = h; }
    void set_vertical  (align::VerticalAlign v)   { vertical = v;   }
    void set_margin    (align::Margin m)          { margin = m;     }

    virtual void render(const components::ComponentBase* comp, SDL_Renderer* rd) = 0;
    
    virtual void init() = 0;
};

struct StringContent : ContentBase {
public:
    StringContent() = default;
    StringContent(const StringContent&);
    virtual ~StringContent() final;

public:
    const static string default_font;

private:
    string value;
    color::RGBA color = (unsigned int)0x000000ff;
    
    string font;
    int size;
    
    TTF_Font* _ttf;
    
public:
    const string& get_value() const { return value; }
    color::RGBA   get_color() const { return color; }
    const string& get_font () const { return font;  }
    int           get_size () const { return size;  }
    
    void set_value(const string& v) { value = v; }
    void set_color(color::RGBA c)   { color = c; }
    void set_font(const string& f, int s) { font = f; size = s; reload_ttf(); }
    
    pair<int, int> get_size();
    
    virtual void render(const components::ComponentBase* comp, SDL_Renderer* rd) final;
    
    void init();

private:
    void reload_ttf() { _ttf = const_cast<TTF_Font*>(gtf.newFont(font, size)); }
    
};

}