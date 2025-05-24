#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/PlayerComponent.hpp"
#include "../Components/SpriteComponent.hpp"

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
                
                if (entity.HasComponent<PlayerComponent>() && entity.HasComponent<SpriteComponent>()
                    && entity.GetComponent<SpriteComponent>().isDead) {
                    transform.position.x += 1;
                    transform.position.y += 1;
                    continue;
                }
                if (entity.HasComponent<SpriteComponent>()
                    && entity.GetComponent<SpriteComponent>().isDead) {
                    continue;
                }
                transform.position.x += rigidBody.velocity.x * rigidBody.speed * dt;
                transform.position.y += rigidBody.velocity.y * rigidBody.speed * dt;
            }
        }

};

#endif // MOVEMENTSYSTEM_HPP