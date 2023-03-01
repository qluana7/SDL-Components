#include "components/label.h"

namespace components {

int Label::event_filter(void* userdata, SDL_Event* e) {
    return 0;
}

color::RGBA Label::_def_fg = 0x00000000;

void Label::set_content(content::StringContent& sc) {
    this->text = const_cast<content::StringContent*>(&sc);
    this->property_changed_event.active(
        this_object,
        event::PropertyChangedEventArgs("content", &text, &sc)
    );
}

void Label::draw(SDL_Renderer* rd) const {
    /* For recovery area */
    SDL_Rect r;
    SDL_RenderGetViewport(rd, &r);

    SDL_Rect area = { (int)this->get_position().x, (int)this->get_position().y, (int)this->_width, (int)this->_height };
    SDL_RenderSetViewport(rd, &area);
    
    if (text != nullptr)
        this->text->render(this, rd);
    
    SDL_RenderSetViewport(rd, &r);
}

void Label::init() {
    this->text = nullptr;
}

void Label::dispose() {
}

Label::~Label() {
    this->dispose();
}

}