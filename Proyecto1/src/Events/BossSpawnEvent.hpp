#ifndef BOSSSPAWNEVENT_HPP
#define BOSSSPAWNEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

class BossSpawnEvent : public Event {
    public:
        Entity a;
        bool isReady;
        BossSpawnEvent(Entity a, bool isReady) : a(a), isReady(isReady) {}
};

#endif // BOSSSPAWNEVENT_HPP