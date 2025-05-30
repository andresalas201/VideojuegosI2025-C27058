/**
 * @file ScriptSystem.hpp
 * @brief Header file for the ScriptSystem class
 */

#ifndef SCRIPTSYSTEM_HPP
#define SCRIPTSYSTEM_HPP
#include <memory>
#include <sol/sol.hpp>
#include <iostream>
#include "../Components/ScriptComponent.hpp"
#include "../Components/EnemyComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Binding/LuaBinding.hpp"

/**
 * @class ScriptSystem
 * @brief System responsible for executing Lua scripts attached to entities
 * 
 * This system processes entities with ScriptComponent and EnemyComponent,
 * executing their associated Lua scripts and providing Lua bindings for
 * game functionality. It serves as the bridge between the ECS system and
 * Lua scripting environment.
 */
class ScriptSystem : public System {
public:
    /**
     * @brief Constructor for ScriptSystem
     * 
     * Creates a new script system instance. No component requirements
     * are set as this system manually checks for specific components.
     */
    ScriptSystem() {
        RequireComponent<ScriptComponent>();
    }
    
    /**
     * @brief Updates and executes Lua scripts for all relevant entities
     * 
     * Iterates through all system entities and executes Lua update scripts
     * for entities with ScriptComponent or EnemyComponent. Sets the global
     * Lua variable "this" to the current entity before script execution.
     * 
     * @param lua Reference to the Sol2 Lua state for script execution
     */
    void Update(sol::state& lua) {
        for (auto& entity : GetSystemEntities()) {
            if (entity.HasComponent<ScriptComponent>()) {
                const auto& script = entity.GetComponent<ScriptComponent>();
                if (script.update.valid()) {
                    lua["this"] = entity;
                    script.update();
                }
                lua.collect_garbage();
            }
        }
    }
    
    /**
     * @brief Creates Lua bindings for game functionality
     * 
     * Sets up the Lua environment with bindings to various game functions,
     * allowing Lua scripts to interact with the game engine. This includes
     * entity manipulation, input handling, scene management, and game mechanics.
     * 
     * @param lua Reference to the Sol2 Lua state to bind functions to
     */
    void CreateLuaBinding(sol::state& lua) {
        //lua.new_usertype<Entity>("entity");
        lua.new_usertype<Entity>("Entity",
            sol::constructors<Entity(int)>(),
            "GetId", &Entity::GetId  // Add whatever basic methods you have
        );
        lua.set_function("is_action_activated", IsActionActivated);
        lua.set_function("set_velocity", SetVelocity);
        lua.set_function("go_to_scene", GoToScene);
        lua.set_function("shoot", Shoot);
        lua.set_function("set_sprite", SetSprite);
        lua.set_function("upgrade_damage", UpgradeDamage);
        lua.set_function("upgrade_amount", UpgradeAmount);
        lua.set_function("upgrade_speed", UpgradeSpeed);
        lua.set_function("background_move", BackgroundMove);
        lua.set_function("spawn_boss", SpawnBoss);
        lua.set_function("set_direction_to_player", SetDirectionToPlayer);
        lua.set_function("set_direction_to_player_boss", SetDirectionToPlayerBoss);
        lua.set_function("follow_player", FollowPlayerSimple);
    }
};
#endif // SCRIPTSYSTEM_HPP