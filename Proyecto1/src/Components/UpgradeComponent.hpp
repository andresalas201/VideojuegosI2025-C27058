#ifndef UPGRADECOMPONENT_HPP
#define UPGRADECOMPONENT_HPP

struct UpgradeComponent {
    int increase;

    UpgradeComponent(int increase = 0) {
        this->increase = increase;
    }
};

#endif // UPGRADECOMPONENT_HPP