#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "components/component.h"

#include "ext/content.h"

#include "event/event_manager.h"
#include "event/event_args.h"

namespace components {

class Label : public ComponentBase {
public:
    Label(Point pt, float w, float h)
        : Label::Label(
            pt, w, h,
            Label::_def_bg,
            Label::_def_fg
        ) { }
    Label(Point pt, float w, float h, color::RGBA bg, color::RGBA fg)
        : ComponentBase::ComponentBase(pt, w, h, bg, fg) { this->init(); }
    Label(float w, float h, align::Margin m, align::HorizontalAlign hz, align::VerticalAlign vt)
        : Label::Label(
            w, h, m, hz, vt,
            Label::_def_bg,
            Label::_def_fg
        ) { }
    Label(float w, float h, align::Margin m, align::HorizontalAlign hz, align::VerticalAlign vt, color::RGBA bg, color::RGBA fg)
        : ComponentBase::ComponentBase(w, h, m, hz, vt, bg, fg) { this->init(); }
    ~Label();

public:
    static color::RGBA _def_fg;
    
public:
    const string name() const final { return "Label"; }
    
    void set_content(const content::StringContent& sc);
    
    void draw(SDL_Renderer* rd) const override;
    void dispose() override;
    
    int event_filter(void* userdata, SDL_Event* event) final;

private:
    content::StringContent* text = nullptr;
    
    void init();
};

}