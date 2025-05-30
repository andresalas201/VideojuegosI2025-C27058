/**
 * @file EnemyComponent.hpp
 * @brief Component for enemy entities in the game system
 */

#ifndef ENEMYCOMPONENT_HPP
#define ENEMYCOMPONENT_HPP
#include <sol/sol.hpp>

class PreEntity;

/**
 * @struct EnemyComponent
 * @brief A component that defines enemy behavior and properties
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to mark entities as enemies and provide them with enemy-specific behavior.
 * It supports custom update logic through Lua scripting, group management
 * for enemy formations or waves, hierarchical relationships, and scoring systems.
 */
struct EnemyComponent {
    /**
     * @brief Lua function for custom enemy update behavior
     * 
     * A Lua script function that defines the enemy's behavior logic,
     * called during the update cycle to handle AI, movement, attacks,
     * or other enemy-specific actions.
     */
    sol::function update;
    
    /**
     * @brief Group identifier for enemy organization
     * 
     * Integer identifier used to group enemies together for coordinated
     * behavior, wave management, or formation control. Enemies with the
     * same group ID can be processed together by relevant systems.
     */
    int group;
    
    /**
     * @brief Pointer to the parent entity that manages this enemy's group
     * 
     * Reference to a PreEntity that serves as the parent or controller
     * for this enemy's group, enabling hierarchical enemy management
     * and group-based behaviors.
     */
    PreEntity* fatherGroup;
    
    /**
     * @brief Score value awarded when this enemy is defeated
     * 
     * The number of points the player receives when this enemy is
     * destroyed or defeated, used for scoring and progression systems.
     */
    int score;
    
    /**
     * @brief Constructor for EnemyComponent
     * 
     * Initializes an enemy component with custom behavior, group management,
     * hierarchical relationships, and scoring properties.
     * 
     * @param update Lua function for enemy behavior logic (default: nil)
     * @param group Group identifier for enemy organization (default: 0)
     * @param fatherGroup Pointer to parent group entity (default: nullptr)
     * @param score Points awarded when enemy is defeated (default: 0)
     */
    EnemyComponent(sol::function update = sol::lua_nil, int group = 0,
                   PreEntity* fatherGroup = nullptr, int score = 0) {
        this->update = update;
        this->group = group;
        this->fatherGroup = fatherGroup;
        this->score = score;
    }
};

#endif // ENEMYCOMPONENT_HPP