#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP


struct HealthComponent {
    int health;
    int damage;

    HealthComponent(int health = 1, int damage = 1) {
        this->health = health;
        this->damage = damage;
    }
};

#endif // HEALTHCOMPONENT_HPP