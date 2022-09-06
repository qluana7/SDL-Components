#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "components/component.h"

#include "event/event_manager.h"
#include "event/event_args.h"

namespace components {

class Slider : public ComponentBase {
public:
    Slider(Point pt, float w, float h)
        : Slider::Slider(
            pt, w, h,
            Slider::_def_bg,
            Slider::_def_fg
        ) { }
    Slider(Point pt, float w, float h, color::RGBA bg, color::RGBA fg)
        : ComponentBase::ComponentBase(pt, w, h, bg, fg) { }
    Slider(float w, float h, align::Margin m, align::HorizontalAlign hz, align::VerticalAlign vt)
        : Slider::Slider(
            w, h, m, hz, vt,
            Slider::_def_bg,
            Slider::_def_fg
        ) { }
    Slider(float w, float h, align::Margin m, align::HorizontalAlign hz, align::VerticalAlign vt, color::RGBA bg, color::RGBA fg)
        : ComponentBase::ComponentBase(w, h, m, hz, vt, bg, fg) { }

public:
    event::EventManager<event::ValueChangedEventArgs> value_changed;
    
public:
    const string name() const final { return "Slider"; }
    
    void draw(SDL_Renderer* rd) const override;
    
    int event_filter(void* userdata, SDL_Event* event) final;
    
private:
    const unordered_map<string, int> spropidx {
        
    };
};

}