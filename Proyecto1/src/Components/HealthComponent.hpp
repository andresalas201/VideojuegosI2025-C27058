#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP


struct HealthComponent {
    int health;
    int damage;
    int lastHit;

    HealthComponent(int health = 1, int damage = 1) {
        this->health = health;
        this->damage = damage;
        this->lastHit = 0;
    }
};

#endif // HEALTHCOMPONENT_HPP