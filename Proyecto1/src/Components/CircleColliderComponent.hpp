/**
 * @file CircleColliderComponent.hpp
 * @brief Component for circular collision detection in the game system
 */

#ifndef CIRCLECOLLIDERCOMPONENT_HPP
#define CIRCLECOLLIDERCOMPONENT_HPP

/**
 * @class CircleColliderComponent
 * @brief A component that provides circular collision detection capabilities
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to enable collision detection for entities. It defines a circular collision
 * boundary along with additional width and height properties for more complex
 * collision scenarios. The component also tracks the collision state of the entity.
 */
class CircleColliderComponent {
public:
    /**
     * @brief The radius of the circular collider
     * 
     * Defines the radius of the circular collision boundary in pixels or game units.
     * Used for circular collision detection calculations.
     */
    int radius;
    
    /**
     * @brief The width dimension of the collider
     * 
     * Additional width property that can be used for rectangular or composite
     * collision detection in conjunction with the circular collider.
     */
    int width;
    
    /**
     * @brief The height dimension of the collider
     * 
     * Additional height property that can be used for rectangular or composite
     * collision detection in conjunction with the circular collider.
     */
    int height;
    
    /**
     * @brief Flag indicating whether the entity is in a "dead" collision state
     * 
     * This boolean flag tracks whether the entity should be considered as
     * having a dead/inactive collision state, which may affect how collision
     * systems process this entity.
     */
    bool isDead;
    
    /**
     * @brief Constructor for CircleColliderComponent
     * 
     * Initializes the circular collider component with specified dimensions.
     * The isDead flag is automatically set to false upon construction.
     * 
     * @param radius The radius of the circular collider (default: 0)
     * @param width The width dimension of the collider (default: 0)
     * @param height The height dimension of the collider (default: 0)
     */
    CircleColliderComponent(int radius = 0, int width = 0, int height = 0) {
        this->radius = radius;
        this->width = width;
        this->height = height;
        this->isDead = false;
    }
};

#endif // CIRCLECOLLIDERCOMPONENT_HPP