/**
 * @file AnimationComponent.hpp
 * @brief Component for managing sprite animation frame sequences
 */

#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <SDL2/SDL.h>

/**
 * @class AnimationComponent
 * @brief ECS component that manages sprite animation sequences
 * 
 * This component handles frame-based animation for sprites by tracking
 * the current frame, animation timing, and playback behavior. It supports
 * both looping and non-looping animations with configurable frame rates.
 */
class AnimationComponent {
public:
    int numFrames;       ///< Total number of frames in the animation sequence
    int currentFrame;    ///< Current frame being displayed (1-based indexing)
    int frameSpeedRate;  ///< Speed multiplier for frame transitions (higher = faster)
    bool isLoop;         ///< Whether the animation should loop when it reaches the end
    int startTime;       ///< SDL tick count when animation started (for timing calculations)

    /**
     * @brief Constructs an AnimationComponent with specified parameters
     * 
     * Initializes the animation component with the given frame count, speed,
     * and looping behavior. Sets the current frame to 1 and records the
     * start time for animation timing calculations.
     * 
     * @param numFrames Total number of frames in the animation (default: 1)
     * @param frameSpeedRate Animation speed multiplier (default: 1)
     * @param isLoop Whether animation should loop continuously (default: true)
     */
    AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true) {
        this->numFrames = numFrames;
        this->currentFrame = 1;
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;
        this->startTime = SDL_GetTicks();
    }
};

#endif // ANIMATIONCOMPONENT_HPP