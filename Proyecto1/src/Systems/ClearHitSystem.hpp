/**
 * @file ClearHitSystem.hpp
 * @brief System for managing hit state duration on sprite entities
 */

#ifndef CLEARHITSYSTEM_HPP
#define CLEARHITSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/SpriteComponent.hpp"

/**
 * @brief System responsible for clearing hit states after a specified duration
 * 
 * The ClearHitSystem manages the visual hit feedback for entities by automatically
 * clearing the hit state after a predetermined time period. This is commonly used
 * for damage indication, invincibility frames, or visual feedback when entities
 * take damage. The system ensures that hit states don't persist indefinitely
 * and provides consistent timing for hit animations or effects.
 */
class ClearHitSystem : public System {
public:
    /**
     * @brief Constructs the clear hit system and sets component requirements
     * 
     * Initializes the system to require SpriteComponent for entities
     * to be processed. The SpriteComponent contains the hit state
     * and timing information needed for hit duration management.
     */
    ClearHitSystem() {
        RequireComponent<SpriteComponent>();
    }

    /**
     * @brief Updates the system by clearing expired hit states
     * @param MILLISECS_PER_FRAME Milliseconds per frame in the game loop
     * @param FPS Frames per second of the game
     * 
     * Processes all entities with hit states and clears the hit flag
     * for entities that have been in the hit state for the specified
     * duration. The hit duration is calculated as:
     * duration = MILLISECS_PER_FRAME * FPS * 1 (1 second)
     * 
     * For each entity:
     * - Skips entities that are not currently in hit state
     * - Checks if the hit duration has exceeded the time limit
     * - Clears the isHit flag when the time limit is reached
     * 
     * This ensures consistent timing for hit visual effects and prevents
     * entities from remaining in hit state indefinitely.
     */
    void Update(int MILLISECS_PER_FRAME, int FPS) {
        Uint32 twoSeconds = MILLISECS_PER_FRAME * FPS * 1;
        for (auto& entity : GetSystemEntities()) {
            Entity& a = entity;
            if (!a.GetComponent<SpriteComponent>().isHit) continue;
            auto& sprite = a.GetComponent<SpriteComponent>();
            if (SDL_GetTicks() - sprite.hitTime >= twoSeconds) {
                sprite.isHit = false;
            }
        }
    }
};

#endif // CLEARHITSYSTEM_HPP