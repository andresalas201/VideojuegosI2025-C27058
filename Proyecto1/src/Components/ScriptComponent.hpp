/**
 * @file ScriptComponent.hpp
 * @brief Component for Lua scripting functionality in the game system
 */

#ifndef SCRIPTCOMPONENT_HPP
#define SCRIPTCOMPONENT_HPP
#include <sol/sol.hpp>
#include <iostream>

/**
 * @struct ScriptComponent
 * @brief A component that provides Lua scripting capabilities for entities
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to enable entities to have custom behavior defined through Lua scripts.
 * It supports both continuous update logic and event-driven click handling,
 * allowing for flexible and customizable entity behaviors without requiring
 * code recompilation.
 */
struct ScriptComponent {
    /**
     * @brief Lua function for continuous update logic
     * 
     * A Lua script function that is called during the entity's update cycle.
     * This function can contain custom AI logic, animation updates, state
     * management, or any other behavior that needs to be executed regularly
     * during gameplay.
     */
    sol::function update;
    
    /**
     * @brief Lua function for click event handling
     * 
     * A Lua script function that is executed when the entity receives
     * a click event. This enables custom click responses, UI interactions,
     * button behaviors, or any other click-based functionality defined
     * through scripting.
     */
    sol::function onClick;
    
    /**
     * @brief Constructor for ScriptComponent
     * 
     * Initializes the script component with Lua functions for update
     * and click event handling. Both functions are optional and can
     * be set to nil if the corresponding functionality is not needed.
     * 
     * @param updateNew Lua function for update logic (default: nil)
     * @param onClickNew Lua function for click event handling (default: nil)
     */
    ScriptComponent(sol::function updateNew = sol::lua_nil,
                    sol::function onClickNew = sol::lua_nil) {
        this->update = updateNew;
        this->onClick = onClickNew;
    }
};

#endif // SCRIPTCOMPONENT_HPP