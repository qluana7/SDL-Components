#pragma once

#include <map>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "ext/pos.h"
#include "ext/align.h"
#include "ext/color.h"
#include "ext/gfxext.h"

#include "event/event_manager.h"
#include "event/event_args.h"

using namespace std;

namespace components {

#define interface class

#define setret(type, member) \
    member = *static_cast<const type*>(data); \
    return &member;
#define psetret(type, member) \
    member = const_cast<type*>(static_cast<const type*>(data)); \
    return &member;

/*
enum class component_type {
    UNKNOWN, BUTTON
};
*/

interface ComponentBase {
public:
    ComponentBase(Point l, float w, float h)
        : ComponentBase::ComponentBase(
            l, w, h,
            ComponentBase::_def_bg,
            ComponentBase::_def_fg
        ) { }
    ComponentBase(Point l, float w, float h, color::RGBA bg, color::RGBA fg)
        : ComponentBase::ComponentBase(
            w, h, align::Margin(l.x, l.y),
            align::HorizontalAlign::LEFT,
            align::VerticalAlign::TOP,
            bg, fg
        ) { }
    ComponentBase(float w, float h, align::Margin m, align::HorizontalAlign hz, align::VerticalAlign vt)
        : ComponentBase::ComponentBase(
            h, w, m, hz, vt,
            ComponentBase::_def_bg,
            ComponentBase::_def_fg
        ) { }
    ComponentBase(float w, float h, align::Margin m, align::HorizontalAlign hz, align::VerticalAlign vt, color::RGBA bg, color::RGBA fg);

public:
    static color::RGBA _def_bg, _def_fg;
    
    event::EventManager<event::MouseEventArgs> mouse_down_event;
    event::EventManager<event::MouseEventArgs> mouse_up_event;
    
    event::EventManager<event::MouseEventArgs> hover_event;
    event::EventManager<event::MouseEventArgs> enter_event;
    event::EventManager<event::MouseEventArgs> leave_event;
    
    event::EventManager<event::SDLEventArgs> focus_event;
    event::EventManager<event::SDLEventArgs> unfocus_event;
    
    /* TODO: PropertyChange template
     * 
     * type : struct
     * name : property
     * 
     * feature
     * - get/set
     * - manage void*
     * - type change support
     */
    event::EventManager<event::PropertyChangedEventArgs> property_changed_event;
    
    Uint32 uid, wid;

protected:
    align::Margin margin;
    align::HorizontalAlign horizontal;
    align::VerticalAlign vertical;
    float _width, _height;
    
    color::RGBA _backgd, _foregd;
    
    bool on_mouse = false;
    bool on_focus = false; // TODO : focus implement
    
public:
    virtual const string name() const = 0;
    
    /* Getter */
    Point get_position() const { return this->margin.map(parent_size, horizontal, vertical); }
    float get_width()    const { return this->_width;  }
    float get_height()   const { return this->_height; }
    
    align::Margin          get_margin()     const { return margin;     }
    align::HorizontalAlign get_horizontal() const { return horizontal; }
    align::VerticalAlign   get_vertical()   const { return vertical;   }
    
    color::RGBA get_background() const { return _backgd; }
    color::RGBA get_foreground() const { return _foregd; }
    
    /* Setter */
    
    void set_position(Point pt);
    void set_width(float w);
    void set_height(float h);
    
    void set_margin(align::Margin m);
    void set_horizontal(align::HorizontalAlign hz);
    void set_vertical(align::VerticalAlign vt);
    
    void set_background(color::RGBA bg);
    void set_foreground(color::RGBA fg);

    virtual void focus()   { on_focus = true;  focus_event.active(this_object, event::SDLEventArgs::empty); }
    virtual void unfocus() { on_focus = false; unfocus_event.active(this_object, event::SDLEventArgs::empty); }
    
    virtual void draw(SDL_Renderer* rd) const = 0;
    virtual void dispose() = 0;
    
    virtual int event_filter(void* userdata, SDL_Event* event) = 0;
    
    // void set_property(const string& name, const void* const data);
    // template<typename _ReturnT>
    // _ReturnT get_property(const string& name) const;
    
    int evft(void* userdata, SDL_Event* event);
    
    // virtual int event_filter(void* userdata, SDL_Event* event) = 0;
    
    Point parent_size;

protected:
    Object this_object = Object(this);

// public:
//     template<typename _ReturnT>
//     const _ReturnT operator[] (const string& name) const { return get_property(name); }

// protected:
//     const unordered_map<string, int> propidx {
//         { "margin",     0 },
//         { "horizontal", 1 },
//         { "vertical",   2 },
//         { "width",      3 },
//         { "height",     4 },
//         { "background", 5 },
//         { "foreground", 6 }
//     };
// 
// protected:
//    virtual void* setprop(const string& name, const void* const data) = 0;
//    virtual const void* getprop(const string& name) const = 0;
};

/*
template <typename _ReturnT>
_ReturnT ComponentBase::get_property(const string& name) const {
    return *(_ReturnT*)getprop(name);
}
*/

class ComponentManager {
public:
    ComponentManager(SDL_Window* win) : window(win)
    { SDL_AddEventWatch(ComponentManager::evft, this); }
    ~ComponentManager()
    { SDL_DelEventWatch(ComponentManager::evft, this); }

    Uint32 add_component(ComponentBase* cp);
    void remove_component(Uint32 uid);
    
    void render(SDL_Renderer* rd);
    
    void clear();
    
private:
    static Uint32 uid;
    SDL_Window* window;
    map<int, ComponentBase*> coms;
    
    static int evft(void* userdata, SDL_Event* e);
};

#undef interface

}