/**
 * @file RigidBodyComponent.hpp
 * @brief Component for physics-based movement and velocity in the game system
 */

#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP
#include <glm/glm.hpp>

/**
 * @struct RigidBodyComponent
 * @brief A component that provides physics-based movement capabilities to entities
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to enable entities to have physics-based movement with velocity and speed
 * properties. It utilizes GLM (OpenGL Mathematics) for 2D vector operations,
 * allowing for smooth directional movement and physics simulations.
 */
struct RigidBodyComponent {
    /**
     * @brief Current velocity vector of the entity
     * 
     * 2D vector representing the entity's velocity in world space.
     * The x component represents horizontal velocity and the y component
     * represents vertical velocity. This vector is used by physics systems
     * to update the entity's position over time.
     */
    glm::vec2 velocity;
    
    /**
     * @brief Speed multiplier for movement calculations
     * 
     * Double value that acts as a speed modifier for the entity's movement.
     * This can be used to scale velocity effects, implement speed boosts
     * or slowdowns, or provide fine-tuned control over movement rates
     * without directly modifying the velocity vector.
     */
    double speed;
    
    /**
     * @brief Constructor for RigidBodyComponent
     * 
     * Initializes the rigid body component with a specified initial velocity.
     * The speed multiplier is automatically set to 1.0, providing normal
     * movement speed without any scaling effects.
     * 
     * @param velocity Initial velocity vector for the entity (default: (0.0, 0.0))
     */
    RigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0)) {
        this->velocity = velocity;
        this->speed = 1;
    }
};

#endif // RIGIDBODYCOMPONENT_HPP