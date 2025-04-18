#ifndef SCRIPTCOMPONENT_HPP
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>
#include <iostream>

struct ScriptComponent {
    sol::function update;
    
    ScriptComponent(sol::function updateNew = sol::lua_nil) {
        this->update = updateNew;
    }
};

#endif // SCRIPTCOMPONENT_HPP