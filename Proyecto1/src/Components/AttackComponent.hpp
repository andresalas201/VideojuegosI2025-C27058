/**
 * @file AttackComponent.hpp
 * @brief Component for managing entity attack capabilities and projectile properties
 */

#ifndef ATTACKCOMPONENT_HPP
#define ATTACKCOMPONENT_HPP

#include <string>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <sol/sol.hpp>

/**
 * @struct AttackComponent
 * @brief ECS component that defines attack behavior and projectile properties
 * 
 * This component encapsulates all parameters needed for entity attacks including
 * damage values, projectile appearance, movement, audio feedback, shot limitations,
 * animation properties, and custom Lua scripting behavior. It supports multi-shot
 * attacks, cooldown management, and flexible projectile customization.
 */
struct AttackComponent {
    int damage;                      ///< Damage dealt by projectiles spawned from this attack
    int radius;                      ///< Collision radius for projectile hit detection
    int width;                       ///< Width of the projectile sprite in pixels
    int height;                      ///< Height of the projectile sprite in pixels
    std::string textureId;           ///< Identifier for the projectile's texture asset
    SDL_Rect srcRect;                ///< Source rectangle for sprite sheet positioning
    glm::vec2 velocity;              ///< Initial velocity vector for spawned projectiles
    std::string shootSoundFilePath;  ///< Path to sound file played when shooting
    std::string hitSoundFilePath;    ///< Path to sound file played when projectile hits
    int maxShots;                    ///< Maximum number of simultaneous active projectiles
    int currentShots;                ///< Current number of active projectiles from this attack
    bool left;                       ///< Direction flag for projectile spawn positioning
    glm::vec2 scale;                 ///< Scale factor applied to spawned projectiles
    int lastShotTick;                ///< SDL tick count of the last shot fired (for cooldown)
    int shotQuantity;                ///< Number of projectiles fired simultaneously per attack
    int numFrames;                   ///< Number of animation frames for projectile sprites
    int frameSpeedRate;              ///< Animation speed multiplier for projectile animation
    bool isLoop;                     ///< Whether projectile animation should loop
    sol::function update;            ///< Lua function called to update projectile behavior

    /**
     * @brief Constructs an AttackComponent with specified attack parameters
     * 
     * Initializes all attack properties including damage, projectile appearance,
     * movement behavior, audio feedback, shot limitations, and animation settings.
     * Sets currentShots to 0 and lastShotTick to 0 for initial state.
     * 
     * @param damage Damage value for projectiles (default: 1)
     * @param radius Collision radius for hit detection (default: 0)
     * @param width Projectile sprite width in pixels (default: 0)
     * @param height Projectile sprite height in pixels (default: 0)
     * @param textureId Asset identifier for projectile texture (default: "none")
     * @param srcX X coordinate in sprite sheet (default: 0)
     * @param srcY Y coordinate in sprite sheet (default: 0)
     * @param velVec Initial velocity vector for projectiles (default: (0,0))
     * @param soundFile Path to shooting sound effect (default: "")
     * @param hitSoundFilePath Path to hit sound effect (default: "none")
     * @param maxShots Maximum simultaneous active projectiles (default: 0)
     * @param left Direction flag for spawn positioning (default: false)
     * @param scale Scale factor for projectile size (default: (1,1))
     * @param shotQuantity Number of projectiles per attack (default: 1)
     * @param numFrames Animation frame count (default: 1)
     * @param frameSpeedRate Animation speed multiplier (default: 1)
     * @param isLoop Whether animation loops (default: true)
     * @param update Lua function for custom projectile behavior (default: nil)
     */
    AttackComponent(int damage = 1, int radius = 0, int width = 0, int height = 0,
                    const std::string& textureId = "none", int srcX = 0, int srcY = 0,
                    glm::vec2 velVec = glm::vec2(0.0, 0.0), std::string soundFile = "",
                    std::string hitSoundFilePath = "none", int maxShots = 0, bool left = false,
                    glm::vec2 scale = glm::vec2(1.0, 1.0), int shotQuantity = 1,
                    int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true,
                    sol::function update = sol::lua_nil) {
        this->damage = damage;
        this->radius = radius;
        this->width = width;
        this->height = height;
        this->textureId = textureId;
        this->srcRect = {srcX, srcY, width, height};
        this->velocity = velVec;
        this->shootSoundFilePath = soundFile;
        this->hitSoundFilePath = hitSoundFilePath;
        this->maxShots = maxShots;
        this->currentShots = 0;
        this->left = left;
        this->scale = scale;
        this->lastShotTick = 0;
        this->shotQuantity = shotQuantity;
        this->numFrames = numFrames;
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;
        this->update = update;
    }
};

#endif // ATTACKCOMPONENT_HPP