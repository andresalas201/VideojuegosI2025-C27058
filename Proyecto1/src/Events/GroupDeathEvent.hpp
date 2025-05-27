#ifndef GROUPEVENT_HPP
#define GROUPEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

class GroupDeathEvent : public Event {
    public:
        Entity a;
        GroupDeathEvent(Entity a) : a(a) {}
};

#endif // GROUPEVENT_HPP