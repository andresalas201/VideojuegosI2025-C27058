#ifndef BOSSACTIVATIONEVENT_HPP
#define BOSSACTIVATIONEVENT_HPP

#include "../EventManager/Event.hpp"

class BossActivationEvent : public Event {
    public:
        bool isActive;
        BossActivationEvent(){
            this->isActive = true;
        };
};

#endif // BOSSACTIVATIONEVENT_HPP