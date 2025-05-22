#ifndef CIRCLECOLLIDERCOMPONENT_HPP
#define CIRCLECOLLIDERCOMPONENT_HPP

class CircleColliderComponent {
    public:
        int radius;
        int width;
        int height;
        bool isDead;

        CircleColliderComponent(int radius = 0, int width = 0, int height = 0) {
            this->radius = radius;
            this->width = width;
            this->height = height;
            this->isDead = false;
        }
};

#endif // CIRCLECOLLIDERCOMPONENT_HPP