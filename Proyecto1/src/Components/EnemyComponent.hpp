#ifndef ENEMYCOMPONENT_HPP
#define ENEMYCOMPONENT_HPP

#include <sol/sol.hpp>


class PreEntity;
struct EnemyComponent {
    sol::function update;
    int group;
    PreEntity* fatherGroup;

    EnemyComponent(sol::function update = sol::lua_nil, int group = 0,
        PreEntity* fatherGroup = nullptr) {
        
        this->update = update;
        this->group = group;
        this->fatherGroup = fatherGroup;
    }
};

#endif // ENEMYCOMPONENT_HPP