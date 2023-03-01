#pragma once

#include <iostream>

#include "ext/align.h"
#include "ext/color.h"
#include "ext/content.h"
#include "ext/object.h"
#include "ext/pos.h"

#define OUTSTREAM basic_ostream<_CharT, _Traits>
#define IOTEMP template<typename _CharT, typename _Traits> \
        inline OUTSTREAM&

template<typename _Tp>
using format_func = function<string (const _Tp&)>;

template<typename _Tp>
struct _Formatter {
    const _Tp& obj; format_func<_Tp> func;
    string operator() () const { return func(obj); }
};

template<typename _Tp>
inline _Formatter<_Tp> formatter(const _Tp& obj, format_func<_Tp> f) {
    return {obj, f};
}

template<typename _Tp, typename _CharT, typename _Traits>
inline OUTSTREAM& operator<< (OUTSTREAM& __os, const _Formatter<_Tp>& f) {
    return __os << f();
}

IOTEMP operator<< (OUTSTREAM& __os, const align::Margin& m) {
    return __os << "{ H: " << m.horizontal << ", V: " << m.vertical << " }";
}

IOTEMP operator<< (OUTSTREAM& __os, const color::RGBA& c) {
    return
    __os << "{ R: 0x" << hex << (int)c.R()
         << ", G: 0x" << hex << (int)c.G()
         << ", B: 0x" << hex << (int)c.B()
         << ", A: 0x" << hex << (int)c.A()
         << " }";
}