/**
 * @file CleanShotSystem.hpp
 * @brief System for cleaning up shot entities that have exceeded their lifetime
 */

#ifndef CLEANSHOTSYSTEM_HPP
#define CLEANSHOTSYSTEM_HPP

#include <iostream>
#include "../ECS/ECS.hpp"
#include "../Components/ShotComponent.hpp"
#include "../Components/FatherComponent.hpp"

/**
 * @brief System responsible for managing shot entity lifetimes and cleanup
 * 
 * The CleanShotSystem manages the lifecycle of projectile entities by removing
 * shots that have existed longer than their maximum allowed lifetime. This
 * prevents accumulation of old projectiles and maintains proper shot counting
 * for entities that fire them. The system uses SDL timing to track shot age
 * and automatically decrements the parent entity's shot counter when cleaning up.
 */
class CleanShotSystem : public System {
private:
    int secondsPerShot; ///< Configurable seconds per shot (currently unused in update logic)

public:
    /**
     * @brief Constructs the clean shot system and sets component requirements
     * 
     * Initializes the system to require ShotComponent and FatherComponent
     * for entities to be processed. The ShotComponent tracks timing information
     * while FatherComponent maintains the relationship to the shooting entity.
     */
    CleanShotSystem() {
        RequireComponent<ShotComponent>();
        RequireComponent<FatherComponent>();
        this->secondsPerShot = 0;
    }

    /**
     * @brief Sets the seconds per shot parameter
     * @param seconds Number of seconds per shot
     * 
     * Configures the seconds per shot value. Note: This parameter is currently
     * not used in the Update() method's lifetime calculations.
     */
    void setSecondsPerShot(int seconds) {
        this->secondsPerShot = seconds;
    }

    /**
     * @brief Updates the system by cleaning up expired shot entities
     * @param MILLISECS_PER_FRAME Milliseconds per frame in the game loop
     * @param FPS Frames per second of the game
     * @param maxSeconds Maximum lifetime for shot entities in seconds
     * 
     * Processes all shot entities and removes those that have exceeded their
     * maximum lifetime. The lifetime is calculated as:
     * maxTime = MILLISECS_PER_FRAME * FPS * maxSeconds
     * 
     * For each expired shot:
     * - Decrements the parent entity's currentShots counter
     * - Logs the cleanup operation for debugging
     * - Marks the shot entity for destruction
     * 
     * This ensures proper resource management and prevents infinite accumulation
     * of projectile entities in the game world.
     */
    void Update(int MILLISECS_PER_FRAME, int FPS, int maxSeconds) {
        Uint32 maxTime = MILLISECS_PER_FRAME * FPS * maxSeconds;
        auto entities = GetSystemEntities();
        for (auto i = entities.begin(); i != entities.end(); i++) {
            Entity a = *i;
            auto& shot = a.GetComponent<ShotComponent>();
            if ((SDL_GetTicks() - shot.shotTime) >= maxTime) {
                a.GetComponent<FatherComponent>().father->currentShots--;
                std::cout << "[CLEANSHOTSYSTEM] Se borra el disparo de entidad "
                    << a.GetId() << std::endl;
                a.Kill();
            }
        }
    }
};

#endif // CLEANSHOTSYSTEM_HPP