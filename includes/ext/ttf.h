#pragma once

#include <unordered_map>
#include <string>

#include <SDL2/SDL_ttf.h>

using namespace std;

class Global_TTF {
public:
    Global_TTF() {
        if (_isinit) return;
        
        if (TTF_Init() < 0) __throw_runtime_error(TTF_GetError());
        
        _isinit = true;
    }    
    
    ~Global_TTF() {
        for (auto [_, f] : _fonts) TTF_CloseFont(f.first);
        _isinit = false;
        TTF_Quit();
    }
    
    const TTF_Font* newFont(const string& name, int size = 11);
    void freeFont(const string& name);

private:
    unordered_map<string, pair<TTF_Font*, int>> _fonts;
    
    static bool _isinit;
};

static Global_TTF gtf;