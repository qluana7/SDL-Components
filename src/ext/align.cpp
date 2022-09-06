#include "ext/align.h"

namespace align {

Point Margin::map(Point size, HorizontalAlign hz, VerticalAlign vt) const {
    Point res;
    
    switch (hz) {
        case HorizontalAlign::LEFT:   res.x = 0;          break;
        case HorizontalAlign::MIDDLE: res.x = size.x / 2; break;
        case HorizontalAlign::RIGHT:  res.x = size.x;     break;
    }
    
    switch (vt) {
        case VerticalAlign::TOP:    res.y = 0;          break;
        case VerticalAlign::MIDDLE: res.y = size.y / 2; break;
        case VerticalAlign::BOTTOM: res.y = size.y;     break;
    }
    
    res.x += this->horizontal; res.y += this->vertical;
    
    return res;
}

Point Margin::map(Point b_sz, Point o_sz, HorizontalAlign hz, VerticalAlign vt) const {
    Point res;
    
    switch (hz) {
        case HorizontalAlign::LEFT:   res.x = 0;                       break;
        case HorizontalAlign::MIDDLE: res.x = b_sz.x / 2 - o_sz.x / 2; break;
        case HorizontalAlign::RIGHT:  res.x = b_sz.x - o_sz.x;         break;
    }
    
    switch (vt) {
        case VerticalAlign::TOP:    res.y = 0;                       break;
        case VerticalAlign::MIDDLE: res.y = b_sz.y / 2 - o_sz.y / 2; break;
        case VerticalAlign::BOTTOM: res.y = b_sz.y - o_sz.y;         break;
    }
    
    res.x += this->horizontal; res.y += this->vertical;
    
    return res;
}

}