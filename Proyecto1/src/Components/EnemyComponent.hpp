#ifndef ENEMYCOMPONENT_HPP
#define ENEMYCOMPONENT_HPP

#include <sol/sol.hpp>


struct EnemyComponent {
    sol::function update;
    int group;

    EnemyComponent(sol::function update = sol::lua_nil, int group = 0) {
        this->update = update;
        this->group = group;
    }
};

#endif // ENEMYCOMPONENT_HPP