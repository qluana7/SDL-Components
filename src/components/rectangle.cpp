#include "components/rectangle.h"

namespace components {

int Rectangle::event_filter(void* userdata, SDL_Event* e) {
    return 0;
}

color::RGBA Rectangle::_def_bd = 0x000000ff;

void Rectangle::draw(SDL_Renderer* rd) const {
    Point p = this->get_position();
    color::RGBA bdc = this->_border, bkc = this->_backgd;

    roundedBoxRGBA(rd,
        p.x, p.y, p.x + this->get_width(), p.y + this->get_height(), this->radius,
        bkc.R(), bkc.G(), bkc.B(), bkc.A()
    );

    roundedRectangleRGBA(rd,
        p.x, p.y, p.x + this->get_width(), p.y + this->get_height(), this->radius,
        bdc.R(), bdc.G(), bdc.B(), bdc.A()
    );
}

void Rectangle::dispose() { }

/*
void* Rectangle::setprop(const string& name, const void* const data) {
    int idx;
    if (propidx.count(name)) idx = propidx.at(name);
    else if (rpropidx.count(name)) idx = rpropidx.at(name);
    else return nullptr;
    
    switch (idx) {
        case 0: setret(align::Margin, margin);
        case 1: setret(align::HorizontalAlign, horizontal);
        case 2: setret(align::VerticalAlign, vertical);
        case 3: setret(float, _width);
        case 4: setret(float, _height);
        case 5: setret(color::RGBA, _backgd);
        case 6: setret(color::RGBA, _foregd);
        
        case 20: setret(color::RGBA, _border);
        case 22: setret(double, radius);
    }
}

const void* Rectangle::getprop(const string& name) const {
    int idx;
    if (propidx.count(name)) idx = propidx.at(name);
    else if (rpropidx.count(name)) idx = rpropidx.at(name);
    else return nullptr;
    
    switch (idx) {
        case 0: return &margin;
        case 1: return &horizontal;
        case 2: return &vertical;
        case 3: return &_width;
        case 4: return &_height;
        case 5: return &_backgd;
        case 6: return &_foregd;
        
        case 20: return &_border;
        case 22: return &radius;
    }
}
*/

}