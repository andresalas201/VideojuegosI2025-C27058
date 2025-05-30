/**
 * @file SoundComponent.hpp
 * @brief Component for managing audio and sound effects in the game system
 */

#ifndef SOUNDCOMPONENT_HPP
#define SOUNDCOMPONENT_HPP
#include <string>

/**
 * @struct SoundComponent
 * @brief A component that associates sound effects with entities
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to enable entities to have associated sound effects. It stores the
 * identifier or path for audio resources, allowing audio systems to
 * play appropriate sounds when entities perform actions, take damage,
 * or trigger specific events.
 */
struct SoundComponent {
    /**
     * @brief Identifier or path for the sound effect
     * 
     * String that specifies the sound effect associated with this entity.
     * This can be a sound file path, a unique identifier for looking up
     * sounds in an audio manager, or a key for accessing pre-loaded
     * audio resources. A value of "none" indicates no sound is associated.
     */
    std::string soundName;
    
    /**
     * @brief Constructor for SoundComponent
     * 
     * Initializes the sound component with a specified sound identifier
     * or path. This allows entities to be associated with specific audio
     * effects for various gameplay events.
     * 
     * @param soundPath The sound identifier or file path (default: "none")
     */
    SoundComponent(const std::string& soundPath = "none") : soundName(soundPath) {}
};

#endif // SOUNDCOMPONENT_HPP