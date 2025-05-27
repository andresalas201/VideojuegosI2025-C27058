#ifndef ENEMYCOMPONENT_HPP
#define ENEMYCOMPONENT_HPP

#include <sol/sol.hpp>


class PreEntity;
struct EnemyComponent {
    sol::function update;
    int group;
    PreEntity* fatherGroup;
    int score;

    EnemyComponent(sol::function update = sol::lua_nil, int group = 0,
        PreEntity* fatherGroup = nullptr, int score = 0) {
        
        this->update = update;
        this->group = group;
        this->fatherGroup = fatherGroup;
        this->score = score;
    }
};

#endif // ENEMYCOMPONENT_HPP