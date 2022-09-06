#include "components/label.h"

namespace components {

int Label::event_filter(void* userdata, SDL_Event* e) {
    return 0;
}

color::RGBA Label::_def_fg = 0x00000000;

void Label::set_content(const content::StringContent& sc) {
    if (text != nullptr) delete text;
    
    content::StringContent* t = new content::StringContent;
    t->value = sc.value;
    t->ttf_location = sc.ttf_location;
    t->pt = sc.pt;
    t->margin = sc.margin;
    t->horizontal = sc.horizontal;
    t->vertical = sc.vertical;
    t->init();
    
    this->text = t;
}

void Label::draw(SDL_Renderer* rd) const {
    /* For recovery area */
    SDL_Rect r;
    SDL_RenderGetViewport(rd, &r);

    SDL_Rect area = { (int)this->get_position().x, (int)this->get_position().y, (int)this->_width, (int)this->_height };
    SDL_RenderSetViewport(rd, &area);
    
    // if (text != nullptr)
    //     this->text->render(this, rd);
    
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