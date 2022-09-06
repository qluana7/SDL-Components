#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "components/component.h"

#include "ext/content.h"

#include "event/event_manager.h"
#include "event/event_args.h"

namespace components {
    
class Button : public ComponentBase {
public:
    Button(Point pt, float w, float h)
        : Button::Button(
            pt, w, h,
            Button::_def_bg,
            Button::_def_fg,
            Button::_def_bd
        ) { }
    Button(Point pt, float w, float h, color::RGBA bg, color::RGBA fg)
        : Button::Button(
            pt, w, h,
            bg, fg,
            Button::_def_bd
        ) { }
    Button(Point pt, float w, float h, color::RGBA bg, color::RGBA fg, color::RGBA bd)
        : ComponentBase::ComponentBase(pt, w, h, bg, fg), _border(bd) { this->init(); }
    Button(float w, float h, align::Margin m, align::HorizontalAlign hz, align::VerticalAlign vt)
        : Button::Button(
            w, h, m, hz, vt,
            Button::_def_bg,
            Button::_def_fg,
            Button::_def_bd
        ) { }
    Button(float w, float h, align::Margin m, align::HorizontalAlign hz, align::VerticalAlign vt, color::RGBA bg, color::RGBA fg, color::RGBA bd)
        : ComponentBase::ComponentBase(w, h, m, hz, vt, bg, fg), _border(bd) { this->init(); }
    ~Button();

public:
    event::EventManager<event::ClickEventArgs> click_event;

public:
    const string name() const final { return "Button"; }
    
    // content::ContentBase* 
    color::RGBA get_border() const { return _border; }
    
    void set_content(content::StringContent& sc);
    void set_border(color::RGBA bd);
    
    void draw(SDL_Renderer* rd) const override;
    void dispose() override;
    
    int event_filter(void* userdata, SDL_Event* event) final;
    
private:
    content::ContentBase* content = nullptr;
    color::RGBA _border;
    
    // const unordered_map<string, int> bpropidx {
    //     { "border",     20 },
    //     { "content",    21 }
    // };
    
    void init();
    // void* setprop(const string& name, const void* const data) final;
    // const void* getprop(const string& name) const final;

    static color::RGBA _def_bd;
};

}