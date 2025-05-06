#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP


struct HealthComponent {
    int health;
    int damage;

    HealthComponent(int health, int damage) {
        this->health = health;
        this->damage = damage;
    }
};

#endif // HEALTHCOMPONENT_HPP