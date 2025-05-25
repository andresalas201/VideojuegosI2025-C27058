#ifndef UPGRADECOMPONENT_HPP
#define UPGRADECOMPONENT_HPP
#include <sol/sol.hpp>

struct UpgradeComponent {
    sol::function upgrade;
    int increase;

    UpgradeComponent(sol::function upgrade = sol::lua_nil, int increase = 1) {
        this->upgrade = upgrade;
        this->increase = increase;
    }
};

#endif // UPGRADECOMPONENT_HPP