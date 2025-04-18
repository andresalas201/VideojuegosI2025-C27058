#ifndef SCRIPTSYSTEM_HPP
#define SCRIPTSYSTEM_HPP

#include <memory>
#include <sol/sol.hpp>
#include <iostream>

#include "../Components/ScriptComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Binding/LuaBinding.hpp"

class ScriptSystem : public System {
    public:
        ScriptSystem() {
            RequireComponent<ScriptComponent>();
        }
        
        void Update(sol::state& lua) {
            for (auto entity : GetSystemEntities()) {
                const auto& script = entity.GetComponent<ScriptComponent>();
                if (script.update.valid()) {
                    lua["this"] = entity;
                    script.update();
                }
            }
        }

        void CreateLuaBinding(sol::state& lua) {
            lua.new_usertype<Entity>("entity");
            lua.set_function("is_action_activated", IsActionActivated);
            lua.set_function("set_velocity", SetVelocity);
        }
};


#endif // SCRIPTSYSTEM_HPP