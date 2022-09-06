#include "components/button.h"

namespace components {

int Button::event_filter(void* userdata, SDL_Event* e) {
    return 0;
}

color::RGBA Button::_def_bd = 0x000000ff;

static void button_click(Object& sender, event::MouseEventArgs e) {
    sender.cast<Button>().click_event.active(sender, event::ClickEventArgs(e));
}

void Button::set_content(content::StringContent& sc) {
    this->content = &sc;
    this->property_changed_event.active(
        this_object,
        event::PropertyChangedEventArgs("content", &content, &sc)
    );
}

void Button::set_border(color::RGBA bd) {
    this->_border = bd;
    this->property_changed_event.active(
        this_object,
        event::PropertyChangedEventArgs("border", &_border, &bd)
    );
}

void Button::draw(SDL_Renderer* rd) const {
    roundedBoxRGBA(rd,
        this->get_position().x, this->get_position().y,
        this->get_position().x + this->_width, this->get_position().y + this->_height,
        5,
        this->_backgd.R(), this->_backgd.G(),
        this->_backgd.B(), this->_backgd.A()
    );
    
    roundedRectangleRGBA(rd,
        this->get_position().x, this->get_position().y,
        this->get_position().x + this->_width, this->get_position().y + this->_height,
        5,
        this->_border.R(), this->_border.G(),
        this->_border.B(), this->_border.A()
    );
    
    /* For recovery area */
    SDL_Rect r;
    SDL_RenderGetViewport(rd, &r);

    SDL_Rect area = { (int)this->get_position().x, (int)this->get_position().y, (int)this->_width, (int)this->_height };
    SDL_RenderSetViewport(rd, &area);
    
    if (content != nullptr)
        this->content->render(this, rd);
    
    SDL_RenderSetViewport(rd, &r);
}

void Button::dispose() {
    // if (this->content != nullptr) delete this->content;
}

void Button::init() {
    this->mouse_down_event += button_click;
}

/*
void* Button::setprop(const string& name, const void* const data) {
    int idx;
    if (propidx.count(name)) idx = propidx.at(name);
    else if (bpropidx.count(name)) idx = bpropidx.at(name);
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
        case 21: psetret(content::ContentBase, content);
    }
}

const void* Button::getprop(const string& name) const {
    int idx;
    if (propidx.count(name)) idx = propidx.at(name);
    else if (bpropidx.count(name)) idx = bpropidx.at(name);
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
        case 21: return &content;
    }
}
*/

Button::~Button() {
    this->dispose();
}

}