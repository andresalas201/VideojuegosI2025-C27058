#ifndef SCRIPTCOMPONENT_HPP
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>
#include <iostream>

struct ScriptComponent {
    sol::function update;
    sol::function onClick;
    sol::function onCollision;
    
    ScriptComponent(sol::function onCollision = sol::lua_nil, 
        sol::function updateNew = sol::lua_nil,
        sol::function onClickNew = sol::lua_nil) {
        this->onCollision = onCollision;
        this->update = updateNew;
        this->onClick = onClickNew;
    }
};

#endif // SCRIPTCOMPONENT_HPP