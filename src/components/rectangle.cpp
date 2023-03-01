#include "components/rectangle.h"

namespace components {

int Rectangle::event_filter(void* userdata, SDL_Event* e) {
    return 0;
}

color::RGBA Rectangle::_def_bd = 0x000000ff;

void Rectangle::set_border(color::RGBA bd) {
    this->_border = bd;
    this->property_changed_event.active(
        this_object,
        event::PropertyChangedEventArgs("border", &_border, &bd)
    );
}

void Rectangle::set_radius(double r) {
    this->_radius = r;
    this->property_changed_event.active(
        this_object,
        event::PropertyChangedEventArgs("radius", &_radius, &r)
    );
}

void Rectangle::draw(SDL_Renderer* rd) const {
    Point p = this->get_position();
    color::RGBA bdc = this->_border, bkc = this->_backgd;

    roundedBoxRGBA(rd,
        p.x, p.y, p.x + this->get_width(), p.y + this->get_height(), this->_radius,
        bkc.R(), bkc.G(), bkc.B(), bkc.A()
    );

    if (bdc != 0) {
        roundedRectangleRGBA(rd,
            p.x, p.y, p.x + this->get_width(), p.y + this->get_height(), this->_radius,
            bdc.R(), bdc.G(), bdc.B(), bdc.A()
        );
    }
}

void Rectangle::dispose() { }

}