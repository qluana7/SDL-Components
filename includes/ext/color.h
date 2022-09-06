#pragma once

#include <SDL2/SDL_render.h>

using namespace std;

namespace color {

class RGBA {
public:
    RGBA() : _r(0xff), _g(0xff), _b(0xff), _a(0xff) { }
    RGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
        : _r(r), _g(g), _b(b), _a(a) {  }
    RGBA(Uint32 hex) { *this = from_ahex(hex); }
    RGBA(const RGBA& o)
        : _r(o.R()), _g(o.G()), _b(o.B()), _a(o.A()) { }

private:
    Uint8 _r, _g, _b, _a;

public:
    SDL_Color color() const {
        return SDL_Color { R(), G(), B(), A() };
    }
    
    Uint8& R() { return _r; } Uint8 R() const { return _r; }
    Uint8& G() { return _g; } Uint8 G() const { return _g; }
    Uint8& B() { return _b; } Uint8 B() const { return _b; }
    Uint8& A() { return _a; } Uint8 A() const { return _a; }
    
    operator Uint32() { return R() << 24 | G() << 16 | B() << 8 | A(); }
    
    static RGBA from_ahex(Uint32 hex) {
        RGBA tmp;
        
        tmp.R() = (hex >> 24) & 0xff;
        tmp.G() = (hex >> 16) & 0xff;
        tmp.B() = (hex >> 8 ) & 0xff;
        tmp.A() = (hex >> 0 ) & 0xff;
        
        return tmp;
    }
    
    static RGBA from_hex(Uint32 hex) {
        RGBA tmp;
        
        tmp.R() = (hex >> 16) & 0xff;
        tmp.G() = (hex >> 8 ) & 0xff;
        tmp.B() = (hex >> 0 ) & 0xff;
        tmp.A() = 0xff;
        
        return tmp;
    }
};

}