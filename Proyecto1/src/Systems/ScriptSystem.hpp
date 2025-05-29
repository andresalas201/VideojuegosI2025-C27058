#ifndef SCRIPTSYSTEM_HPP
#define SCRIPTSYSTEM_HPP

#include <memory>
#include <sol/sol.hpp>
#include <iostream>

#include "../Components/ScriptComponent.hpp"
#include "../Components/EnemyComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Binding/LuaBinding.hpp"

class ScriptSystem : public System {
    public:
        ScriptSystem() {
        }
        
        void Update(sol::state& lua) {
            for (auto entity : GetSystemEntities()) {
                if (entity.HasComponent<ScriptComponent>()) {
                    const auto& script = entity.GetComponent<ScriptComponent>();
                    if (script.update.valid()) {
                        lua["this"] = entity;
                        script.update();
                    }
                }
                if (entity.HasComponent<EnemyComponent>()) {
                    const auto& enemy = entity.GetComponent<ScriptComponent>();
                    if (enemy.update.valid()) {
                        lua["this"] = entity;
                        enemy.update();
                    }
                }
            }
        }

        void CreateLuaBinding(sol::state& lua) {
            lua.new_usertype<Entity>("entity");
            
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
        }
};


#endif // SCRIPTSYSTEM_HPP