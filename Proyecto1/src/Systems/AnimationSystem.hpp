/**
 * @file AnimationSystem.hpp
 * @brief Animation system for managing sprite-based animations in the ECS framework
 */

#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include <SDL2/SDL.h>
#include "../ECS/ECS.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"

/**
 * @brief System responsible for updating sprite animations
 * 
 * The AnimationSystem manages time-based sprite animations by updating
 * the current frame of animated sprites based on elapsed time and frame rate.
 * It operates on entities that have both AnimationComponent and SpriteComponent.
 * 
 * The system calculates frame progression using SDL's timer functionality
 * and updates the source rectangles for sprite rendering, including support
 * for hit detection and death animation rectangles.
 */
class AnimationSystem : public System {
public:
    /**
     * @brief Constructs the animation system and sets component requirements
     * 
     * Initializes the system to require both AnimationComponent and SpriteComponent
     * for entities to be processed by this system.
     */
    AnimationSystem() {
        RequireComponent<AnimationComponent>();
        RequireComponent<SpriteComponent>();
    }

    /**
     * @brief Updates all animated entities in the system
     * 
     * Processes each entity with animation capabilities by:
     * - Calculating the current frame based on elapsed time and frame speed
     * - Updating the sprite's source rectangle for rendering
     * - Updating collision and death animation rectangles
     * 
     * The frame calculation uses the formula:
     * currentFrame = ((currentTime - startTime) * frameSpeedRate / 1000) % numFrames
     * 
     * This ensures smooth frame transitions and proper looping of animations.
     */
    void Update() {
        for (auto entity: GetSystemEntities()) {
            auto& animation = entity.GetComponent<AnimationComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();
            
            // Calculate current frame based on elapsed time and frame rate
            animation.currentFrame = ((SDL_GetTicks() - animation.startTime) *
                animation.frameSpeedRate / 1000) % animation.numFrames;
            
            // Update sprite source rectangles for different animation states
            sprite.srcRect.x = sprite.srcRectBase + animation.currentFrame * sprite.width;
            sprite.hitSrcRect.x = sprite.hitSrcRectBase + animation.currentFrame * sprite.width;
            sprite.deathRect.x = sprite.deathBaseX + animation.currentFrame * sprite.width;
        }
    }

private:
    // No private members currently needed
};

#endif // ANIMATIONSYSTEM_HPP