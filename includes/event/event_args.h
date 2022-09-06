#pragma once

#include <string>
#include <ctime>
#include <stddef.h>

#include <SDL2/SDL_events.h>

#include "ext/pos.h"
#include "ext/object.h"

#define uint unsigned int
#define ushort unsigned short

using namespace std;

namespace event {

class EventArgs {
public:
    virtual uint time() const = 0;
};

class SDLEventArgs : public EventArgs {
public:
    SDLEventArgs(const SDL_Event& ev) : event(ev) { }
    SDLEventArgs(const SDLEventArgs& e) : SDLEventArgs(e.event) { }
    
private:
    SDLEventArgs() = default;
    
public:
    uint time() const override { return event.common.timestamp; }

public:
    const static SDLEventArgs empty;

protected:
    SDL_Event event;
};

/* Mouse Events */
enum class MouseButton : ushort
{ LEFT = 1, MIDDLE, RIGHT, X1, X2 };

class ClickEventArgs : public SDLEventArgs {
public:
    ClickEventArgs(const SDL_Event& ev) : SDLEventArgs(ev), data(ev.button) { }
    ClickEventArgs(const SDLEventArgs& e) : SDLEventArgs(e), data(event.button) { }
    
    uint time() const override { return data.timestamp; }
    
    uint m_id() const { return data.which; }
    uint w_id() const { return data.windowID; }
    ushort clicks() const { return data.clicks; }
    Point pos() const { return { static_cast<float>(data.x), static_cast<float>(data.y) }; }
    MouseButton button() const { return (MouseButton)data.button; }
private:
    SDL_MouseButtonEvent data;
};

class MouseEventArgs : public SDLEventArgs {
public:
    MouseEventArgs(const SDL_Event& ev) : SDLEventArgs(ev), data(ev.motion) { }
    MouseEventArgs(const SDLEventArgs& e) : SDLEventArgs(e), data(event.motion) { }
    
    uint time() const override { return data.timestamp; }
    
    uint m_id() const { return data.which; }
    uint w_id() const { return data.windowID; }
    uint button_flag() const { return data.state; }
    Point pos() const { return { static_cast<float>(data.x), static_cast<float>(data.y) }; }
    Point relative_pos() const { return { static_cast<float>(data.xrel), static_cast<float>(data.yrel) }; }
private:
    SDL_MouseMotionEvent data;
};

/* Slider */
class ValueChangedEventArgs : public EventArgs {
public:
    ValueChangedEventArgs(float before, float current)
        : before_value(before), current_value(current) {
            _time = ::time(nullptr);
    }
        
public:
    uint time() const override { return _time; }

public:
    const float before_value, current_value;

private:
    uint _time;
};

/* Common */
class PropertyChangedEventArgs : public EventArgs {
public:
    PropertyChangedEventArgs(const string& name, const Object& prop, const Object& cv)
        : property_name(name), property(prop), changed(cv) {
        _time = ::time(nullptr);
    }

public:
    uint time() const override { return _time; }
public:
    const string property_name;
    const Object& property;
    const Object& changed;
    
private:
    uint _time;
};

}