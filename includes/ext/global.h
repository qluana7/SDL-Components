#pragma once

#include <string>

#include "align.h"
#include "color.h"

using namespace std;

class Global {
private:
    int pt;
    string ttf_location;
    
    align::Margin mg;
    color::RGBA bg, fg;
};