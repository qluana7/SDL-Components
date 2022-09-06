#pragma once

#include <SDL2/SDL2_gfxPrimitives.h>

SDL2_GFXPRIMITIVES_SCOPE int thickEllipseColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint32 color, Uint8 thick);
SDL2_GFXPRIMITIVES_SCOPE int thickEllipseRGBA(SDL_Renderer * renderer, Sint16 xc, Sint16 yc, Sint16 xr, Sint16 yr, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 thick);
SDL2_GFXPRIMITIVES_SCOPE int thickArcColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint32 color, Uint8 thick);
SDL2_GFXPRIMITIVES_SCOPE int thickArcRGBA(SDL_Renderer * renderer, Sint16 xc, Sint16 yc, Sint16 rad, Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 thick);
SDL2_GFXPRIMITIVES_SCOPE int thickCircleColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint32 color, Uint8 thick);
SDL2_GFXPRIMITIVES_SCOPE int thickCircleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 thick);