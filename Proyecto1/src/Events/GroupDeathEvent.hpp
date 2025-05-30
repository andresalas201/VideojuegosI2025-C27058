/**
 * @file GroupEvent.hpp
 * @brief Defines the GroupDeathEvent class for handling group entity death events
 */

#ifndef GROUPEVENT_HPP
#define GROUPEVENT_HPP
#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @class GroupDeathEvent
 * @brief Event class that represents the death of a group entity
 * 
 * This class inherits from the Event base class and is used to notify
 * systems when a group entity has died. It carries information about the
 * group entity that triggered the death event.
 */
class GroupDeathEvent : public Event {
public:
    /**
     * @brief The group entity that has died
     * 
     * This member holds the Entity representing the group that triggered
     * this death event.
     */
    Entity a;
    
    /**
     * @brief Constructs a new GroupDeathEvent
     * 
     * @param a The Entity representing the group that has died
     */
    GroupDeathEvent(Entity a) : a(a) {}
};
#endif // GROUPEVENT_HPP