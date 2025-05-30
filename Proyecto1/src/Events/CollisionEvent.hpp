/**
 * @file CollisionEvent.hpp
 * @brief Defines the CollisionEvent class for handling entity collision events
 */

#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP
#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @class CollisionEvent
 * @brief Event class that represents a collision between two entities
 * 
 * This class inherits from the Event base class and is used to notify
 * systems when two entities collide. It carries information about both
 * entities involved in the collision.
 */
class CollisionEvent : public Event {
public:
    /**
     * @brief The first entity involved in the collision
     */
    Entity a;
    
    /**
     * @brief The second entity involved in the collision
     */
    Entity b;
    
    /**
     * @brief Constructs a new CollisionEvent
     * 
     * @param a The first entity in the collision
     * @param b The second entity in the collision
     */
    CollisionEvent(Entity a, Entity b): a(a), b(b) {}
    
private:
};
#endif // COLLISIONEVENT_HPP