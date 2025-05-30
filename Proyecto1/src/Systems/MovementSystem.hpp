/**
 * @file MovementSystem.hpp
 * @brief Movement system implementation for ECS architecture
 */

#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP
#include "../ECS/ECS.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/PlayerComponent.hpp"
#include "../Components/SpriteComponent.hpp"

/**
 * @class MovementSystem
 * @brief System responsible for updating entity positions based on physics
 * 
 * This system handles the movement of entities by updating their transform positions
 * based on their rigid body velocity and speed. It includes special handling for
 * dead entities, with different behavior for players versus other entities.
 */
class MovementSystem : public System {
public:
    /**
     * @brief Constructor for MovementSystem
     * 
     * Sets up the system to require RigidBodyComponent and TransformComponent
     * for all entities it will process.
     */
    MovementSystem() {
        RequireComponent<RigidBodyComponent>();
        RequireComponent<TransformComponent>();
    }

    /**
     * @brief Updates entity positions based on physics calculations
     * 
     * @param dt Delta time in seconds for frame-rate independent movement
     * 
     * Iterates through all entities with movement components and updates their
     * positions. Special handling is applied for dead entities:
     * - Dead players continue moving diagonally (drift effect)
     * - Other dead entities stop moving entirely
     * - Living entities move according to velocity, speed, and delta time
     */
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