#ifndef UPGRADECOMPONENT_HPP
#define UPGRADECOMPONENT_HPP
#include <sol/sol.hpp>

struct UpgradeComponent {
    sol::function upgrade;

    UpgradeComponent(sol::function upgrade = sol::lua_nil) {
        this->upgrade = upgrade;
    }
};

#endif // UPGRADECOMPONENT_HPP