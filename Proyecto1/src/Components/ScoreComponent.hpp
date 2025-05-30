/**
 * @file ScoreComponent.hpp
 * @brief Component for managing scoring systems and boss-related score logic
 */

#ifndef SCORECOMPONENT_HPP
#define SCORECOMPONENT_HPP
#include <sol/sol.hpp>

/**
 * @struct ScoreComponent
 * @brief A component that manages scoring functionality with special boss handling
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to provide entities with scoring capabilities. It supports both regular
 * scoring mechanics and special boss-related scoring logic through Lua
 * scripting, enabling flexible and customizable scoring systems.
 */
struct ScoreComponent {
    /**
     * @brief Flag indicating whether this entity contributes to scoring
     * 
     * Boolean flag that determines if this entity should be processed
     * by scoring systems. When true, the entity participates in score
     * calculations and related scoring mechanics.
     */
    bool isScore;
    
    /**
     * @brief Lua function for custom boss score validation logic
     * 
     * A Lua script function that can be executed to perform custom
     * checks or calculations related to boss scoring. This allows for
     * complex scoring conditions, bonus calculations, or special
     * boss defeat requirements beyond simple score addition.
     */
    sol::function checkBoss;
    
    /**
     * @brief Score value specifically for boss-related scoring
     * 
     * Integer representing the score value associated with boss
     * encounters or boss-specific scoring events. This may be
     * awarded when defeating bosses or meeting boss-related
     * scoring conditions.
     */
    int bossScore;
    
    /**
     * @brief Constructor for ScoreComponent
     * 
     * Initializes the score component with boss scoring capabilities
     * and custom validation logic. The isScore flag is automatically
     * set to true, making the entity participate in scoring systems.
     * 
     * @param bossScore Score value for boss-related events (default: 0)
     * @param checkBoss Lua function for boss score validation (default: nil)
     */
    ScoreComponent(int bossScore = 0, sol::function checkBoss = sol::lua_nil) {
        this->isScore = true;
        this->bossScore = bossScore;
        this->checkBoss = checkBoss;
    }
};

#endif // SCORECOMPONENT_HPP