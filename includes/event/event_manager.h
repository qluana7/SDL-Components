#pragma once

#include <map>
#include <memory>
#include <functional>

#include "event_args.h"

#include "ext/object.h"

using namespace std;

namespace event {

template <typename _ArgT = EventArgs>
class EventManager {
    
using event_func = function<void(Object&, _ArgT)>;

public:
    int  add_event(event_func f);
    void remove_event(int uid);

    void active(Object& sender, _ArgT e);
    
    int  operator+= (event_func f) { return this->add_event(f); }
    void operator-= (int uid) { this->remove_event(uid); }
private:
    int ev_uid = 0;

    map<int, event_func> events;
};

template <typename _ArgT>
int EventManager<_ArgT>::add_event(event_func f) {
    events[ev_uid] = f;
    return ev_uid++;
}

template <typename _ArgT>
void EventManager<_ArgT>::remove_event(int uid) {
    if (events.count(uid) == 0) throw uid;
    
    events.erase(uid);
}

template <typename _ArgT>
void EventManager<_ArgT>::active(Object& sender, _ArgT e) {
    for (auto& f : this->events) f.second(sender, e);
}

}