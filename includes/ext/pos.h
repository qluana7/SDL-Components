#pragma once

struct Point {
    Point() = default;
    Point(float _x, float _y) : x(_x), y(_y) { }
    
    float x, y;
    
    Point operator+ (Point p) { return Point(x + p.x, y + p.y); }
    Point operator- (Point p) { return Point(x - p.x, y - p.y); }
    Point operator* (Point p) { return Point(x * p.x, y * p.y); }
    Point operator/ (Point p) { return Point(x / p.x, y / p.y); }
    
    void operator+= (Point p) { this->x += p.x; this->y += p.y; }
    void operator-= (Point p) { this->x -= p.x; this->y -= p.y; }
    void operator*= (Point p) { this->x *= p.x; this->y *= p.y; }
    void operator/= (Point p) { this->x /= p.x; this->y /= p.y; }
    
    bool operator== (Point p) { return (x == p.x) && (y == p.y); }
    bool operator!= (Point p) { return *this != p; }
};