#ifndef HEALTHBARCOMPONENT_HPP
#define HEALTHBARCOMPONENT_HPP

struct HealthBarComponent {
    bool isPlayer1;
    int health;

    HealthBarComponent(bool isPlayer1 = true ,int health = 0) {
        this->isPlayer1 = isPlayer1;
        this->health = health;
    }
};

#endif // HEALTHBARCOMPONENT_HPP