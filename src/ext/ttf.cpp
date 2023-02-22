#include <ext/ttf.h>

bool Global_TTF::_isinit = false;

const TTF_Font* Global_TTF::newFont(const string& name, int size) {
    TTF_Font* tf = nullptr;
    
    if (!_fonts.count(name)) {
        TTF_Font* t = TTF_OpenFont(name.data(), size);
        
        if (t == nullptr) __throw_runtime_error(TTF_GetError());
        
        _fonts[name] = {t, 1};
    } else _fonts[name].second++;
    
    tf = _fonts[name].first;
    if (TTF_SetFontSize(tf, size) < 0) return nullptr;
    
    return tf;
}

void Global_TTF::freeFont(const string& name) {
    if (!_fonts.count(name)) return;
    
    auto& value = _fonts[name];
    
    if (value.second == 1) _fonts.erase(name);
    else value.second--;
}