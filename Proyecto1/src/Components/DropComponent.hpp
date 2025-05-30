/**
 * @file DropComponent.hpp
 * @brief Component for handling dropped items and collectibles in the game system
 */

#ifndef DROPCOMPONENT_HPP
#define DROPCOMPONENT_HPP
#include <sol/sol.hpp>

/**
 * @struct DropComponent
 * @brief A component that represents collectible items dropped in the game world
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to create entities that represent dropped items or collectibles. These items
 * can provide various benefits when collected, including stat increases,
 * upgrades through Lua scripting, visual and audio feedback, and collision detection.
 */
struct DropComponent {
    /**
     * @brief The numerical increase value provided by this drop
     * 
     * Represents the amount by which a player's stat (health, score, etc.)
     * should be increased when this drop is collected.
     */
    int increase;
    
    /**
     * @brief The radius for collision detection
     * 
     * Defines the circular collision boundary for detecting when
     * the player or other entities interact with this drop.
     */
    int radius;
    
    /**
     * @brief Lua function for custom upgrade behavior
     * 
     * A Lua script function that can be executed when the drop is collected,
     * allowing for complex custom upgrade logic beyond simple stat increases.
     */
    sol::function upgrade;
    
    /**
     * @brief The width of the drop's visual representation
     * 
     * Defines the width dimension for rendering the drop's sprite or texture.
     */
    int width;
    
    /**
     * @brief The height of the drop's visual representation
     * 
     * Defines the height dimension for rendering the drop's sprite or texture.
     */
    int height;
    
    /**
     * @brief The rotation angle of the drop
     * 
     * Specifies the rotation angle in degrees for rendering the drop,
     * allowing for rotated visual presentation.
     */
    double rotation;
    
    /**
     * @brief The texture identifier for the drop's visual appearance
     * 
     * String identifier used to look up the appropriate texture/sprite
     * for rendering this drop in the game world.
     */
    std::string textureId;
    
    /**
     * @brief Source rectangle for texture clipping
     * 
     * SDL rectangle defining the portion of the texture to use when
     * rendering this drop, enabling sprite sheet usage.
     */
    SDL_Rect srcRect;
    
    /**
     * @brief Sound effect name to play when collected
     * 
     * String identifier for the sound effect that should be played
     * when the player collects this drop.
     */
    std::string soundName;
    
    /**
     * @brief Constructor for DropComponent
     * 
     * Initializes a drop component with all necessary properties for
     * visual rendering, collision detection, audio feedback, and upgrade effects.
     * 
     * @param increase The stat increase value provided by this drop (default: 1)
     * @param upgrade Lua function for custom upgrade behavior (default: nil)
     * @param width Width of the drop's visual representation (default: 0)
     * @param height Height of the drop's visual representation (default: 0)
     * @param rotation Rotation angle in degrees (default: 0)
     * @param textureId Texture identifier string (default: "none")
     * @param srcX X coordinate of the source rectangle (default: 0)
     * @param srcY Y coordinate of the source rectangle (default: 0)
     * @param soundName Sound effect identifier (default: "none")
     * @param radius Collision detection radius (default: 0)
     */
    DropComponent(int increase = 1, sol::function upgrade = sol::lua_nil, int width = 0,
    int height = 0, double rotation = 0, const std::string& textureId = "none",
    int srcX = 0, int srcY = 0, const std::string& soundName = "none", int radius = 0) {
        this->increase = increase;
        this->upgrade = upgrade;
        this->width = width;
        this->height = height;
        this->rotation = rotation;
        this->textureId = textureId;
        this->srcRect = {srcX, srcY, width, height};
        this->soundName = soundName;
        this->radius = radius;
    }
};

#endif // DROPCOMPONENT_HPP