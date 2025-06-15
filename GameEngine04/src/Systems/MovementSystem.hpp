#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"

class MovementSystem : public System {

    public:
        MovementSystem() {
            RequireComponent<RigidBodyComponent>();
            RequireComponent<TransformComponent>();
        }

        void Update(double dt) {
            for (auto entity : GetSystemEntities()) {
                auto& transform = entity.GetComponent<TransformComponent>();
                auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
                transform.previousPosition = transform.position;

                if (rigidBody.isDynamic) {
                    rigidBody.acceleration = rigidBody.sumForces * rigidBody.invMass;
                    rigidBody.velocity += rigidBody.acceleration * static_cast<float>(dt);
                    transform.position += rigidBody.velocity * static_cast<float>(dt);
                    rigidBody.sumForces = glm::vec2(0);
                } else {
                    transform.position.x += rigidBody.velocity.x * dt;
                    transform.position.y += rigidBody.velocity.y * dt;
                }

                
                
            }
        }

};

#endif // MOVEMENTSYSTEM_HPP