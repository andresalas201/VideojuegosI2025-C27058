#ifndef BOSSSPAWNEVENT_HPP
#define BOSSSPAWNEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

class BossSpawnEvent : public Event {
    public:
        Entity a;
        BossSpawnEvent(Entity a) : a(a) {}
};

#endif // BOSSSPAWNEVENT_HPP