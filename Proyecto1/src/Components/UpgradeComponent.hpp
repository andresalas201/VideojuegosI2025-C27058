#ifndef UPGRADECOMPONENT_HPP
#define UPGRADECOMPONENT_HPP
#include <sol/sol.hpp>

/**
 * @brief A component for managing upgrades and enhancement effects.
 * 
 * UpgradeComponent stores upgrade-related data including a Lua function
 * that defines the upgrade behavior and a numeric value representing the
 * magnitude of the upgrade effect. This component is typically used in
 * game systems for handling player upgrades, item enhancements, or
 * progressive improvements to entities.
 */
struct UpgradeComponent {
    /** @brief Lua function that defines the upgrade behavior or effect */
    sol::function upgrade;
    
    /** @brief Numeric value representing the magnitude or level of the upgrade */
    int increase;
    
    /**
     * @brief Constructs an UpgradeComponent with specified upgrade function and value.
     * 
     * Creates an UpgradeComponent with the given Lua function for upgrade logic
     * and an integer value representing the upgrade magnitude. The Lua function
     * can be used to implement custom upgrade behaviors that are scriptable
     * and modifiable at runtime.
     * 
     * @param upgrade Lua function that implements the upgrade logic (default: sol::lua_nil)
     * @param increase Integer value representing the upgrade magnitude or level (default: 1)
     */
    UpgradeComponent(sol::function upgrade = sol::lua_nil, int increase = 1) {
        this->upgrade = upgrade;
        this->increase = increase;
    }
};

#endif // UPGRADECOMPONENT_HPP