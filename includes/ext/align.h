#pragma once

#pragma once

#include "pos.h"

namespace align {

enum class HorizontalAlign {
    LEFT, MIDDLE, RIGHT
};

enum class VerticalAlign {
    TOP, MIDDLE, BOTTOM
};

struct Margin {
    Margin() = default;
    Margin(float h, float v)
        : horizontal(h), vertical(v) { }
    Margin(float l, float t, float r, float b)
        : horizontal(l - r), vertical(t - b) { }
    
    float horizontal, vertical;
    
    Point map(Point size, HorizontalAlign hz, VerticalAlign vt) const;
    Point map(Point b_sz, Point o_sz, HorizontalAlign hz, VerticalAlign vt) const;
};

}