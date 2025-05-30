/**
 * @file ShotComponent.hpp
 * @brief Component for managing projectile and shot entities in the game system
 */

#ifndef SHOTCOMPONENT_HPP
#define SHOTCOMPONENT_HPP
#include <SDL2/SDL.h>

/**
 * @struct ShotComponent
 * @brief A component that identifies and manages projectile entities
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to mark entities as projectiles or shots. It tracks the shot's origin
 * (player vs enemy), timing information for lifecycle management, and
 * provides essential data for projectile systems to handle collision
 * detection, cleanup, and behavior logic.
 */
struct ShotComponent {
    /**
     * @brief Flag indicating whether this entity is a shot/projectile
     * 
     * Boolean flag that identifies this entity as a shot or projectile.
     * This is used by systems to quickly identify and process projectile
     * entities for movement, collision detection, and cleanup operations.
     */
    bool isShot;
    
    /**
     * @brief Flag indicating whether this shot was fired by a player
     * 
     * Boolean flag that distinguishes between player-fired projectiles
     * and enemy-fired projectiles. This is crucial for collision detection
     * systems to determine which entities should be damaged by the shot
     * and for applying different visual or behavioral effects.
     */
    bool playerShot;
    
    /**
     * @brief Timestamp when the shot was created
     * 
     * Integer storing the SDL tick count when this shot entity was created.
     * This timestamp is used for implementing shot lifetime limits, fade
     * effects, or other time-based behaviors like automatic cleanup of
     * old projectiles to prevent memory leaks.
     */
    int shotTime;
    
    /**
     * @brief Constructor for ShotComponent
     * 
     * Initializes the shot component with shot identification and origin flags.
     * The shot creation time is automatically recorded using SDL_GetTicks()
     * for precise timing and lifecycle management.
     * 
     * @param isShot Flag indicating if this entity is a shot (default: true)
     * @param playerShot Flag indicating if shot was fired by player (default: false)
     */
    ShotComponent (bool isShot = true, bool playerShot = false) {
        this->isShot = isShot;
        this->shotTime = SDL_GetTicks();
        this->playerShot = playerShot;
    }
};

#endif // SHOTCOMPONENT_HPP