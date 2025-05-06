#ifndef DEATHEVENT_HPP
#define DEATHEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

class DeathEvent : public Event {
    public:
        Entity a;

        DeathEvent(Entity a): a(a) {}
};

#endif // DEATHEVENT_HPP