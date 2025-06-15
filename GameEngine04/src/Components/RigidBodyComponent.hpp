#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <glm/glm.hpp>

struct RigidBodyComponent {
    bool isDynamic;
    bool isSolid;
    
    glm::vec2 sumForces = glm::vec2(0.0f);
    glm::vec2 acceleration = glm::vec2(0.0f);
    glm::vec2 velocity = glm::vec2(0.0f);

    float mass;
    float invMass;

    RigidBodyComponent(bool isDynamic = false, float mass = 1,
        bool isSolid = true) {
        this->isDynamic = isDynamic;
        this->mass = mass;
        this->invMass = 1.0f / mass;
        this->velocity = velocity;
        this->isSolid = isSolid;
    }
};

#endif // RIGIDBODYCOMPONENT_HPP