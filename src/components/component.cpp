#include "components/component.h"

#include <iostream>

namespace components {

#define in_range(x, x1, x2) ((x1) <= (x) && (x) <= (x2))
#define on_object(obj, x ,y) \
        in_range(x, obj->get_position().x, obj->get_position().x + obj->_width) && \
        in_range(y, obj->get_position().y, obj->get_position().y + obj->_height)

color::RGBA ComponentBase::_def_bg = 0xcfcfcfff;
color::RGBA ComponentBase::_def_fg = 0x000000ff;

int ComponentBase::evft(void* userdata, SDL_Event* event) {
    ComponentBase* comp = (ComponentBase*)userdata;
    Object obj = userdata;
    
    if (event->type == SDL_MOUSEBUTTONDOWN ||
        event->type == SDL_MOUSEBUTTONUP   ||
        event->type == SDL_MOUSEMOTION) {
        if ((event->type == SDL_MOUSEMOTION ? event->motion.windowID : event->button.windowID) != comp->wid) return 0;
        
        int x = event->button.x, y = event->button.y;
        
        if (on_object(comp, x, y)) {
            if (comp->on_mouse == false) {
                comp->enter_event.active(obj, event::MouseEventArgs(*event));
                comp->on_mouse = true;
            }
            
            comp->hover_event.active(obj, event::MouseEventArgs(*event));
            
            if (event->type == SDL_MOUSEBUTTONDOWN)
                comp->mouse_down_event.active(obj, event::MouseEventArgs(*event));
            else if (event->type == SDL_MOUSEBUTTONUP)
                comp->mouse_up_event.active(obj, event::MouseEventArgs(*event));
        } else {
            if (comp->on_mouse == true) {
                comp->leave_event.active(obj, event::MouseEventArgs(*event));
                comp->on_mouse = false;
            }
        }
    }
    
    return 0;
}

Uint32 ComponentManager::uid = 0;

ComponentBase::ComponentBase(
    float w, float h, align::Margin m,
    align::HorizontalAlign hz, align::VerticalAlign vt,
    color::RGBA bg, color::RGBA fg
) : margin(m), horizontal(hz), vertical(vt), _width(w), _height(h), _backgd(bg), _foregd(fg) {
    /*
    int ww, wh;
    SDL_Window* win = SDL_GetWindowFromID(this->wid);
    SDL_GetWindowSize(win, &ww, &wh);
    
    loc = m.map(Point(ww, wh), hz, vt);
    */
}

void ComponentBase::set_position(Point pt) {
    this->margin = align::Margin(pt.x, pt.y);
    this->property_changed_event.active(
        this_object, event::PropertyChangedEventArgs("margin", &this->margin, &pt)
    );
}

void ComponentBase::set_width(float w) {
    this->_width = w;
    this->property_changed_event.active(
        this_object, event::PropertyChangedEventArgs("width", &this->_width, &w)
    );
}

void ComponentBase::set_height(float h) {
    this->_height = h;
    this->property_changed_event.active(
        this_object, event::PropertyChangedEventArgs("height", &this->_height, &h)
    );
}

void ComponentBase::set_margin(align::Margin m) {
    this->margin = m;
    this->property_changed_event.active(
        this_object, event::PropertyChangedEventArgs("margin", &this->margin, &m)
    );
}

void ComponentBase::set_horizontal(align::HorizontalAlign hz) {
    this->horizontal = hz;
    this->property_changed_event.active(
        this_object, event::PropertyChangedEventArgs("horizontal", &this->horizontal, &hz)
    );
}

void ComponentBase::set_vertical(align::VerticalAlign vt) {
    this->vertical = vt;
    this->property_changed_event.active(
        this_object, event::PropertyChangedEventArgs("vertical", &this->vertical, &vt)
    );
}

void ComponentBase::set_background(color::RGBA bg) {
    this->_backgd = bg;
    this->property_changed_event.active(
        this_object, event::PropertyChangedEventArgs("background", &this->_backgd, &bg)
    );
}

void ComponentBase::set_foreground(color::RGBA fg) {
    this->_foregd = fg;
    this->property_changed_event.active(
        this_object, event::PropertyChangedEventArgs("foreground", &this->_foregd, &fg)
    );
}

/*
void ComponentBase::set_property(const string& name, const void* const data) {
    const void* const prop = setprop(name, data);
    
    event::PropertyChangedEventArgs p(name, prop, data);
    
    property_changed_event.active(this, p);
}
*/

Uint32 ComponentManager::add_component(ComponentBase* cp) {
    cp->uid = ComponentManager::uid;
    
    coms[cp->uid] = cp;
    
#ifdef DEBUG
    cout << uid << " Added.\n";
#endif
    
    this->uid++;
    
    cp->wid = SDL_GetWindowID(this->window);
    int w, h; SDL_GetWindowSize(window, &w, &h);
    cp->parent_size = Point(w, h);
    
    return cp->uid;
}

void ComponentManager::remove_component(Uint32 uid) {
    coms[uid]->dispose();
    coms.erase(uid);

#ifdef DEBUG
    cout << uid << " Deleted.\n";
#endif
}

void ComponentManager::render(SDL_Renderer* rd) {
    for (const auto& c : coms) c.second->draw(rd);
}

void ComponentManager::clear() {
    vector<Uint32> v;
    for (const auto& c : coms) v.push_back(c.first);
    for (Uint32 i : v) remove_component(i);

#ifdef DEBUG
    cout << "Component clear finish\n";
#endif
}

int ComponentManager::evft(void* userdata, SDL_Event* e) {
    ComponentManager* mgr = ((ComponentManager*)userdata);
    
    for (const auto& o : mgr->coms) {
        o.second->evft(o.second, e);
        o.second->event_filter(o.second, e);
    }
    
    return 0;
}

}