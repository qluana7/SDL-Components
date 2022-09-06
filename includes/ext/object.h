#pragma once

class Object {
public:
    Object() : data(nullptr) { }
    Object(void* dt) : data(dt) { }
    
private:
    void* data;
    
public:
    template<typename _CastT>
    _CastT& cast() { return *static_cast<_CastT*>(data); }
};