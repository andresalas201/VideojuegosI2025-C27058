/**
 * @file SpriteComponent.hpp
 * @brief Component for managing sprite rendering and animation states in the game system
 */

#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP
#include <SDL2/SDL.h>
#include <string>

/**
 * @struct SpriteComponent
 * @brief A component that manages sprite rendering with multiple animation states
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to provide entities with visual representation through sprites. It supports
 * multiple animation states including normal, hit, and death animations,
 * with flexible sprite sheet management and state-based visual feedback.
 */
struct SpriteComponent {
    /**
     * @brief Identifier for the texture/sprite sheet
     * 
     * String identifier used to look up the appropriate texture resource
     * for rendering this sprite. This corresponds to a loaded texture
     * in the game's asset management system.
     */
    std::string textureId;
    
    /**
     * @brief Width of the sprite in pixels
     * 
     * The width dimension of the sprite for rendering calculations
     * and collision detection purposes.
     */
    int width;
    
    /**
     * @brief Height of the sprite in pixels
     * 
     * The height dimension of the sprite for rendering calculations
     * and collision detection purposes.
     */
    int height;
    
    /**
     * @brief Source rectangle for normal sprite rendering
     * 
     * SDL rectangle defining the portion of the texture to use when
     * rendering the sprite in its normal state. This enables sprite
     * sheet usage and animation frame selection.
     */
    SDL_Rect srcRect;
    
    /**
     * @brief Source rectangle for hit state rendering
     * 
     * SDL rectangle defining the portion of the texture to use when
     * the entity is in a hit state, providing visual feedback for
     * damage or collision events.
     */
    SDL_Rect hitSrcRect;
    
    /**
     * @brief Flag indicating whether the entity is currently in hit state
     * 
     * Boolean flag that determines if the sprite should be rendered
     * using hit state visuals, typically triggered by damage events.
     */
    bool isHit;
    
    /**
     * @brief Timestamp when the hit state was triggered
     * 
     * Integer storing when the hit state began, used for timing
     * hit visual effects and returning to normal state.
     */
    int hitTime;
    
    /**
     * @brief Counter for controlling hit state display duration
     * 
     * Integer counter used to control how long the hit state visuals
     * are displayed before returning to normal rendering.
     */
    int showHitCounter;
    
    /**
     * @brief Base X coordinate for normal state source rectangle
     * 
     * Stores the original X position of the normal state source rectangle,
     * used as a reference point for sprite sheet navigation and animation.
     */
    int srcRectBase;
    
    /**
     * @brief Base X coordinate for hit state source rectangle
     * 
     * Stores the original X position of the hit state source rectangle,
     * used as a reference point for hit animation frames.
     */
    int hitSrcRectBase;
    
    /**
     * @brief X coordinate for upward movement animation frame
     * 
     * X position in the sprite sheet for the animation frame displayed
     * when the entity is moving upward or in an "up" state.
     */
    int upX;
    
    /**
     * @brief X coordinate for downward movement animation frame
     * 
     * X position in the sprite sheet for the animation frame displayed
     * when the entity is moving downward or in a "down" state.
     */
    int downX;
    
    /**
     * @brief X coordinate for upward movement during hit state
     * 
     * X position in the sprite sheet for the hit animation frame
     * displayed when the entity is moving upward while in hit state.
     */
    int hitUpX;
    
    /**
     * @brief X coordinate for downward movement during hit state
     * 
     * X position in the sprite sheet for the hit animation frame
     * displayed when the entity is moving downward while in hit state.
     */
    int hitDownX;
    
    /**
     * @brief Base X coordinate for death animation
     * 
     * Stores the starting X position for death animation frames,
     * used as a reference point for death state sprite sequences.
     */
    int deathBaseX;
    
    /**
     * @brief Source rectangle for death state rendering
     * 
     * SDL rectangle defining the portion of the texture to use when
     * the entity is in death state, enabling death animations.
     */
    SDL_Rect deathRect;
    
    /**
     * @brief Flag indicating whether the entity is in death state
     * 
     * Boolean flag that determines if the sprite should be rendered
     * using death state visuals and animations.
     */
    bool isDead;
    
    /**
     * @brief Timestamp when the death state was triggered
     * 
     * Integer storing when the death state began, used for timing
     * death animations and cleanup operations.
     */
    int deathTime;
    
    /**
     * @brief Constructor for SpriteComponent
     * 
     * Initializes the sprite component with comprehensive animation state support.
     * Sets up normal, hit, and death rendering states with configurable sprite
     * sheet coordinates for flexible animation management.
     * 
     * @param textureId Identifier for the sprite texture (default: "none")
     * @param width Width of the sprite in pixels (default: 0)
     * @param height Height of the sprite in pixels (default: 0)
     * @param srcRectX X coordinate of normal state source rectangle (default: 0)
     * @param srcRectY Y coordinate of normal state source rectangle (default: 0)
     * @param hitRectX X coordinate of hit state source rectangle (default: 0)
     * @param hitRectY Y coordinate of hit state source rectangle (default: 0)
     * @param upX X coordinate for upward movement frame (default: 0)
     * @param downX X coordinate for downward movement frame (default: 0)
     * @param hitUpX X coordinate for upward movement hit frame (default: 0)
     * @param hitDownX X coordinate for downward movement hit frame (default: 0)
     * @param deathRectX X coordinate of death state source rectangle (default: 0)
     * @param deathRectY Y coordinate of death state source rectangle (default: 0)
     */
    SpriteComponent(const std::string& textureId = "none", int width = 0,
    int height = 0, int srcRectX = 0, int srcRectY = 0,
    int hitRectX = 0, int hitRectY = 0, int upX = 0, int downX = 0,
    int hitUpX = 0, int hitDownX = 0, int deathRectX = 0,
    int deathRectY = 0) {
        this->textureId = textureId;
        this->width = width;
        this->height = height;
        this->srcRect = {srcRectX, srcRectY, width, height};
        this->srcRectBase = srcRectX;
        this->hitSrcRect = {hitRectX, hitRectY, width, height};
        this->hitSrcRectBase = hitRectX;
        this->isHit = false;
        this->showHitCounter = 0;
        this->upX = upX;
        this->downX = downX;
        this->hitUpX = hitUpX;
        this->hitDownX = hitDownX;
        this->deathRect = {deathRectX, deathRectY, width, height};
        this->deathBaseX = deathRectX;
        this->isDead = false;
    }
};

#endif // SPRITECOMPONENT_HPP