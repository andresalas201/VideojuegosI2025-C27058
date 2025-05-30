/**
 * @file HealthComponent.hpp
 * @brief Component for managing entity health and damage in the game system
 */

#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

/**
 * @struct HealthComponent
 * @brief A component that manages an entity's health, damage, and hit tracking
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to provide entities with health management capabilities. It tracks current
 * health points, damage values for attacks, and timing information for hit
 * detection and invincibility frames or damage cooldowns.
 */
struct HealthComponent {
    /**
     * @brief Current health points of the entity
     * 
     * Integer representing the entity's remaining health. When this value
     * reaches zero or below, the entity is typically considered defeated
     * or destroyed by relevant game systems.
     */
    int health;
    
    /**
     * @brief Damage value that this entity deals when attacking
     * 
     * Integer representing the amount of damage this entity inflicts
     * on other entities during combat or collision interactions.
     */
    int damage;
    
    /**
     * @brief Timestamp or frame count of the last hit received
     * 
     * Integer tracking when this entity was last damaged, used for
     * implementing invincibility frames, damage cooldowns, or visual
     * feedback systems that need to know about recent damage events.
     */
    int lastHit;
    
    /**
     * @brief Constructor for HealthComponent
     * 
     * Initializes the health component with specified health and damage values.
     * The lastHit timestamp is automatically set to 0, indicating no recent hits.
     * 
     * @param health Initial health points for the entity (default: 1)
     * @param damage Damage value for attacks by this entity (default: 1)
     */
    HealthComponent(int health = 1, int damage = 1) {
        this->health = health;
        this->damage = damage;
        this->lastHit = 0;
    }
};

#endif // HEALTHCOMPONENT_HPP