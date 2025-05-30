/**
 * @file DeathEvent.hpp
 * @brief Defines the DeathEvent class for handling entity death events
 */

#ifndef DEATHEVENT_HPP
#define DEATHEVENT_HPP
#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @class DeathEvent
 * @brief Event class that represents the death of an entity
 * 
 * This class inherits from the Event base class and is used to notify
 * systems when an entity has died. It carries information about the
 * entity that triggered the death event.
 */
class DeathEvent : public Event {
public:
    /**
     * @brief The entity that has died
     * 
     * This member holds the Entity that triggered this death event.
     */
    Entity a;
    
    /**
     * @brief Constructs a new DeathEvent
     * 
     * @param a The Entity that has died
     */
    DeathEvent(Entity a): a(a) {}
};
#endif // DEATHEVENT_HPP