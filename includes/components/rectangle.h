#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "components/component.h"

#include "ext/pos.h"

#include "event/event_manager.h"
#include "event/event_args.h"

namespace components {

class Rectangle : public ComponentBase {
public:
    Rectangle(Point pt, float w, float h)
        : Rectangle::Rectangle(
            pt, w, h,
            Rectangle::_def_bg,
            Rectangle::_def_bd
        ) { }
    Rectangle(Point pt, float w, float h, color::RGBA bg, color::RGBA bd)
        : ComponentBase::ComponentBase(pt, w, h, bg, Rectangle::_def_fg) { this->_border = bd; }
    Rectangle(Point pt, float w, float h, align::Margin m, align::HorizontalAlign hz, align::VerticalAlign vt, color::RGBA bg, color::RGBA bd)
        : ComponentBase::ComponentBase(w, h, m, hz, vt, bg, _def_fg), _border(bd) { }

public:
    const string name() const final { return "Rectangle"; }
    
    color::RGBA get_border() const { return _border; }
    double      get_radius() const { return _radius;  }

    void set_border(color::RGBA bd);
    void set_radius(double r);

    void draw(SDL_Renderer* rd) const override;
    void dispose() override;
    
    int event_filter(void* userdata, SDL_Event* event) final;

private:
    double _radius;
    color::RGBA _border;
    
    static color::RGBA _def_bd;
};

}