/**
 * @file FatherComponent.hpp
 * @brief Component for establishing parent-child relationships with attack entities
 */

#ifndef FATHERCOMPONENT_HPP
#define FATHERCOMPONENT_HPP
#include "AttackComponent.hpp"

/**
 * @struct FatherComponent
 * @brief A component that establishes a parent-child relationship with an attack entity
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to create hierarchical relationships between entities and attack components.
 * It allows entities to maintain a reference to a parent attack entity,
 * enabling behaviors like projectiles tracking their source, child entities
 * inheriting properties from parents, or coordinated attack patterns.
 */
struct FatherComponent {
    /**
     * @brief Pointer to the parent attack component
     * 
     * Reference to an AttackComponent that serves as the parent or source
     * for this entity. This enables the entity to access parent attack
     * properties, coordinate with the parent's behavior, or inherit
     * attack characteristics from the parent entity.
     */
    AttackComponent* father;
    
    /**
     * @brief Constructor for FatherComponent
     * 
     * Initializes the component with a reference to a parent attack component,
     * establishing the parent-child relationship for attack-related behaviors.
     * 
     * @param father Pointer to the parent AttackComponent (default: nullptr)
     */
    FatherComponent (AttackComponent* father = nullptr) : father(father) {}
};

#endif // FATHERCOMPONENT_HPP