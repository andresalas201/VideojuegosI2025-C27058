/**
 * @file BossSpawnEvent.hpp
 * @brief Defines the BossSpawnEvent class for handling boss entity spawn events
 */

#ifndef BOSSSPAWNEVENT_HPP
#define BOSSSPAWNEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @class BossSpawnEvent
 * @brief Event class that represents the spawning of a boss entity
 * 
 * This class inherits from the Event base class and is used to notify
 * systems when a boss entity has been spawned in the game world.
 * It carries information about the spawned boss entity.
 */
class BossSpawnEvent : public Event
{
public:
    /**
     * @brief The boss entity that was spawned
     * 
     * This member holds the Entity representing the boss that triggered
     * this spawn event.
     */
    Entity a;

    /**
     * @brief Constructs a new BossSpawnEvent
     * 
     * @param a The Entity representing the boss that was spawned
     */
    BossSpawnEvent(Entity a) : a(a) {}
};

#endif // BOSSSPAWNEVENT_HPP