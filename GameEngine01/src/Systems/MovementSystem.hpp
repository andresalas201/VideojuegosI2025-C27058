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
                const auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
                
                transform.position.x += rigidBody.velocity.x * dt;
                transform.position.y += rigidBody.velocity.y * dt;
            }
        }

};

#endif // MOVEMENTSYSTEM_HPP