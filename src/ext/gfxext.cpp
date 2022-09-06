#include "ext/gfxext.h"

// Extensions for thick outline ellipses and arcs by Richard Russell 19-Feb-2019

// SDL_RenderDrawLine() is documented as including both end points, but this isn't
// reliable in Linux so use SDL_RenderDrawPoints() instead, despite being slower.
static int renderdrawline(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{
	int result ;
#ifndef __EMSCRIPTEN__
	if ((x1 == x2) && (y1 == y2))
		result = SDL_RenderDrawPoint (renderer, x1, y1) ;
	else if (y1 == y2)
	    {
		int x ;
		if (x1 > x2) { x = x1 ; x1 = x2 ; x2 = x ; }
		SDL_Point *points = (SDL_Point*) malloc ((x2 - x1 + 1) * sizeof(SDL_Point)) ;
		if (points == NULL) return -1 ;
		for (x = x1; x <= x2; x++)
		    {
			points[x - x1].x = x ;
			points[x - x1].y = y1 ;
		    }
		result = SDL_RenderDrawPoints (renderer, points, x2 - x1 + 1) ;
		free (points) ;
	    }
	else if (x1 == x2)
	    {
		int y ;
		if (y1 > y2) { y = y1 ; y1 = y2 ; y2 = y ; }
		SDL_Point *points = (SDL_Point*) malloc ((y2 - y1 + 1) * sizeof(SDL_Point)) ;
		if (points == NULL) return -1 ;
		for (y = y1; y <= y2; y++)
		    {
			points[y - y1].x = x1 ;
			points[y - y1].y = y ;
		    }
		result = SDL_RenderDrawPoints (renderer, points, y2 - y1 + 1) ;
		free (points) ;
	    }
	else
#endif
		result = SDL_RenderDrawLine (renderer, x1, y1, x2, y2) ;
	return result ;
}

static int hlinecliparc(SDL_Renderer *renderer, int x1, int x2, int y, int xc, int yc, double s, double f)
{
	int result = 0 ;
	double a1, a2 ;
	a1 = atan2(y, x1) ;
	a2 = atan2(y, x2) ;
	if (a1 > a2)
	    {
		double a = a1 ; a1 = a2 ; a2 = a ;
		int x = x1 ; x1 = x2 ; x2 = x ;
	    }
	if (f < s)
	    {
		if ((a1 > f) && (a2 < s)) return result ;
		if ((a1 < s) && (a1 > f)) x1 = y / tan(s) ;
		if ((a2 > f) && (a2 < s)) x2 = y / tan(f) ;
		if ((a1 < f) && (a2 > s))
		    {
			result |= renderdrawline(renderer, x1+xc, y+yc, y/tan(f)+xc, y+yc) ;
			result |= renderdrawline(renderer, y/tan(s)+xc, y+yc, x2+xc, y+yc) ;
			return result ;
		    }
	    }
	else
	    {
		if ((a1 > f) || (a2 < s)) return result ;
		if (a1 < s) x1 = y / tan(s) ;
		if (a2 > f) x2 = y / tan(f) ;
	    }
	result |= renderdrawline(renderer, x1+xc, y+yc, x2+xc, y+yc) ;
	return result ;
}

/*!
\brief Draw thick ellipse with blending.
\param renderer The renderer to draw on.
\param xc X coordinate of the center of the ellipse.
\param yc Y coordinate of the center of the ellipse.
\param xr Horizontal radius in pixels of the ellipse.
\param yr Vertical radius in pixels of the ellipse.
\param r The red value of the ellipse to draw. 
\param g The green value of the ellipse to draw. 
\param b The blue value of the ellipse to draw. 
\param a The alpha value of the ellipse to draw.
\param thick The line thickness in pixels
\returns Returns 0 on success, -1 on failure.
*/
int thickEllipseRGBA(SDL_Renderer * renderer, Sint16 xc, Sint16 yc, Sint16 xr, Sint16 yr, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 thick)
{
	int result = 0 ;
	int xi, yi, xo, yo, x, y, z ;
	double xi2, yi2, xo2, yo2 ;

	if (thick <= 1)
		return ellipseRGBA(renderer, xc, yc, xr, yr, r, g, b, a) ;

	xi = xr - thick / 2 ;
	xo = xi + thick - 1 ;
	yi = yr - thick / 2 ;
	yo = yi + thick - 1 ;

	if ((xi <= 0) || (yi <= 0))
		return -1 ;

	xi2 = xi * xi ;
	yi2 = yi * yi ;
	xo2 = xo * xo ;
	yo2 = yo * yo ;

	if (a != 255) result |= SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	if (xr < yr)
	    {
		for (x = -xo; x <= -xi; x++)
		    {
			y = sqrt(yo2 * (1.0 - x*x/xo2)) + 0.5 ;
			result |= renderdrawline(renderer, xc+x, yc-y, xc+x, yc+y) ;
		    }
		for (x = -xi + 1; x <= xi - 1; x++)
		    {
			y = sqrt(yo2 * (1.0 - x*x/xo2)) + 0.5 ;
			z = sqrt(yi2 * (1.0 - x*x/xi2)) + 0.5 ;
			result |= renderdrawline(renderer, xc+x, yc+z, xc+x, yc+y) ;
			result |= renderdrawline(renderer, xc+x, yc-z, xc+x, yc-y) ;
		    }
		for (x = xo; x >= xi; x--)
		    {
			y = sqrt(yo2 * (1.0 - x*x/xo2)) + 0.5 ;
			result |= renderdrawline(renderer, xc+x, yc-y, xc+x, yc+y) ;
		    }
	    }
	else
	    {
		for (y = -yo; y <= -yi; y++)
		    {
			x = sqrt(xo2 * (1.0 - y*y/yo2)) + 0.5 ;
			result |= renderdrawline(renderer, xc-x, yc+y, xc+x, yc+y) ;
		    }
		for (y = -yi + 1; y <= yi - 1; y++)
		    {
			x = sqrt(xo2 * (1.0 - y*y/yo2)) + 0.5 ;
			z = sqrt(xi2 * (1.0 - y*y/yi2)) + 0.5 ;
			result |= renderdrawline(renderer, xc+z, yc+y, xc+x, yc+y) ;
			result |= renderdrawline(renderer, xc-z, yc+y, xc-x, yc+y) ;
		    }
		for (y = yo; y >= yi; y--)
		    {
			x = sqrt(xo2 * (1.0 - y*y/yo2)) + 0.5 ;
			result |= renderdrawline(renderer, xc-x, yc+y, xc+x, yc+y) ;
		    }
	    }
	return result ;
}

/*!
\brief thick Arc with blending.
\param renderer The renderer to draw on.
\param xc X coordinate of the center of the arc.
\param yc Y coordinate of the center of the arc.
\param rad Radius in pixels of the arc.
\param start Starting radius in degrees of the arc. 0 degrees is right, increasing clockwise.
\param end Ending radius in degrees of the arc. 0 degrees is right, increasing clockwise.
\param r The red value of the arc to draw. 
\param g The green value of the arc to draw. 
\param b The blue value of the arc to draw. 
\param a The alpha value of the arc to draw.
\param thick The line thickness in pixels.
\returns Returns 0 on success, -1 on failure.
*/
int thickArcRGBA(SDL_Renderer * renderer, Sint16 xc, Sint16 yc, Sint16 rad, Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 thick)
{
	int result = 0 ;
	int ri, ro, x, y, z ;
	double ri2, ro2, s, f ;

	if (thick <= 1)
		return arcRGBA(renderer, xc, yc, rad, start, end, r, g, b, a) ;

	while (start < -180) start += 360 ;
	while (start >= 180) start -= 360 ;
	while (end < -180) end += 360 ;
	while (end >= 180) end -= 360 ;
	s = M_PI * (double)start / 180.0 ;
	f = M_PI * (double)end / 180.0 ;
	if (start == end) return 0 ;

	ri = rad - thick / 2 ;
	ro = ri + thick - 1 ;
	if (ri <= 0) return -1 ;

	ri2 = ri * ri ;
	ro2 = ro * ro ;

	if (a != 255) result |= SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	result |= SDL_SetRenderDrawColor(renderer, r, g, b, a);

	for (y = -ro; y <= -ri; y++)
	    {
		x = sqrt(ro2 * (1.0 - y*y/ro2)) + 0.5 ;
		result |= hlinecliparc(renderer, -x, x, y, xc, yc, s, f) ;
	    }
	for (y = -ri + 1; y <= ri - 1; y++)
	    {
		x = sqrt(ro2 * (1.0 - y*y/ro2)) + 0.5 ;
		z = sqrt(ri2 * (1.0 - y*y/ri2)) + 0.5 ;
		result |= hlinecliparc(renderer, z, x, y, xc, yc, s, f) ;
		result |= hlinecliparc(renderer, -z, -x, y, xc, yc, s, f) ;
	    }
	for (y = ro; y >= ri; y--)
	    {
		x = sqrt(ro2 * (1.0 - y*y/ro2)) + 0.5 ;
		result |= hlinecliparc(renderer, -x, x, y, xc, yc, s, f) ;
	    }
	return result ;
}

// returns Returns 0 on success, -1 on failure.
int thickCircleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a, Uint8 thick)
{
	return thickEllipseRGBA(renderer, x, y, rad, rad, r, g, b, a, thick);
}

// returns Returns 0 on success, -1 on failure.
int thickEllipseColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint32 color, Uint8 thick)
{
	Uint8 *c = (Uint8 *)&color; 
	return thickEllipseRGBA(renderer, x, y, rx, ry, c[0], c[1], c[2], c[3], thick);
}

// returns Returns 0 on success, -1 on failure.
int thickArcColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Sint16 start, Sint16 end, Uint32 color, Uint8 thick)
{
	Uint8 *c = (Uint8 *)&color; 
	return thickArcRGBA(renderer, x, y, rad, start, end, c[0], c[1], c[2], c[3], thick);
}

// returns Returns 0 on success, -1 on failure.
int thickCircleColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad, Uint32 color, Uint8 thick)
{
	Uint8 *c = (Uint8 *)&color; 
	return thickEllipseRGBA(renderer, x, y, rad, rad, c[0], c[1], c[2], c[3], thick);
}