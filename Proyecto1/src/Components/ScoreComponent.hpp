#ifndef SCORECOMPONENT_HPP
#define SCORECOMPONENT_HPP

#include <sol/sol.hpp>
struct ScoreComponent {
    bool isScore;
    sol::function checkBoss;
    int bossScore;

    ScoreComponent(int bossScore = 0, sol::function checkBoss = sol::lua_nil) {
        this->isScore = true;
        this->bossScore = bossScore;
        this->checkBoss = checkBoss;
    }
};

#endif // SCORECOMPONENT_HPP