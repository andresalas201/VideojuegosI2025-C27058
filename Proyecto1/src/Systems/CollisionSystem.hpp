/**
 * @file CollisionSystem.hpp
 * @brief System for detecting and handling circular collision detection between entities
 */

#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include <glm/glm.hpp>
#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/ShotComponent.hpp"
#include "../Components/UpgradeComponent.hpp"
#include "../Components/PlayerComponent.hpp"
#include "../Components/EnemyComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @brief System responsible for detecting circular collisions between entities
 * 
 * The CollisionSystem performs collision detection using circular bounds for all
 * entities with CircleColliderComponent. It implements game-specific collision
 * rules to determine which entity types should interact with each other, and
 * emits CollisionEvent when valid collisions are detected. The system uses
 * efficient nested loop iteration with collision filtering to avoid unnecessary
 * calculations and prevent invalid interactions.
 */
class CollisionSystem : public System {
public:
    /**
     * @brief Constructs the collision system and sets component requirements
     * 
     * Initializes the system to require CircleColliderComponent for entities
     * to be processed. Additional components like TransformComponent are
     * accessed as needed during collision detection.
     */
    CollisionSystem() {
        RequireComponent<CircleColliderComponent>();
    }

    /**
     * @brief Updates the collision system by checking all entity pairs for collisions
     * @param eventManager Event manager for emitting collision events
     * 
     * Performs collision detection between all valid entity pairs using the following process:
     * 1. Iterates through all entities with collision components
     * 2. Applies game-specific collision filtering rules to skip invalid pairs
     * 3. Calculates circular collision detection for valid pairs
     * 4. Emits CollisionEvent for detected collisions
     * 
     * Collision filtering rules prevent interactions between:
     * - Same entity with itself
     * - Shot-to-shot collisions
     * - Player shots hitting the player who fired them
     * - Player-to-player collisions
     * - Enemy-to-enemy collisions
     * - Enemy shots hitting enemies
     * - Non-player entities collecting upgrades
     * - Dead colliders (isDead flag set)
     * 
     * The system uses nested loops with iterator optimization to check each
     * pair only once, improving performance for large numbers of entities.
     */
    void Update(std::unique_ptr<EventManager>& eventManager) {
        auto entities = GetSystemEntities();
        for (auto i = entities.begin(); i != entities.end(); i++) {
            Entity a = *i;
            auto aCollider = a.GetComponent<CircleColliderComponent>();
            auto aTransform = a.GetComponent<TransformComponent>();
            if (aCollider.isDead) continue;
            
            for (auto j = i; j != entities.end(); j++) {
                Entity b = *j;
                
                // Skip invalid collision pairs based on game rules
                if (a == b ||
                    (a.HasComponent<ShotComponent>() && b.HasComponent<ShotComponent>()) ||
                    (a.HasComponent<UpgradeComponent>()) ||
                    (b.HasComponent<ShotComponent>() && (a.HasComponent<PlayerComponent>()) &&
                     (b.GetComponent<ShotComponent>().playerShot)) ||
                    (a.HasComponent<PlayerComponent>() && b.HasComponent<PlayerComponent>()) ||
                    ((!a.HasComponent<PlayerComponent>() || a.HasComponent<ShotComponent>()) &&
                     (b.HasComponent<UpgradeComponent>())) ||
                    (a.HasComponent<EnemyComponent>() && b.HasComponent<EnemyComponent>()) ||
                    (a.HasComponent<EnemyComponent>() && b.HasComponent<ShotComponent>()
                     && !b.GetComponent<ShotComponent>().playerShot) ||
                    (b.HasComponent<EnemyComponent>() && a.HasComponent<ShotComponent>()
                     && !a.GetComponent<ShotComponent>().playerShot)) {
                    continue;
                }
                
                auto bCollider = b.GetComponent<CircleColliderComponent>();
                auto bTransform = b.GetComponent<TransformComponent>();
                if (bCollider.isDead) continue;
                
                // Calculate collision center positions accounting for scale
                glm::vec2 aCenterPos = glm::vec2{
                    aTransform.position.x + (aCollider.width / 2) * aTransform.scale.x,
                    aTransform.position.y + (aCollider.height / 2) * aTransform.scale.y
                };
                glm::vec2 bCenterPos = glm::vec2{
                    bTransform.position.x + (bCollider.width / 2) * bTransform.scale.x,
                    bTransform.position.y + (bCollider.height / 2) * bTransform.scale.y
                };
                
                // Calculate scaled radii
                int aRadius = aCollider.radius * aTransform.scale.x;
                int bRadius = bCollider.radius * bTransform.scale.x;
                
                // Check for circular collision
                bool collision = CheckCircullarCollision(aRadius, bRadius, aCenterPos, bCenterPos);
                if (collision) {
                    eventManager->EmitEvent<CollisionEvent>(a, b);
                }
            }
        }
    }

    /**
     * @brief Checks if two circles are colliding
     * @param aRadius Radius of the first circle
     * @param bRadius Radius of the second circle
     * @param aPos Center position of the first circle
     * @param bPos Center position of the second circle
     * @return true if the circles are colliding, false otherwise
     * 
     * Performs circular collision detection using the distance formula.
     * Two circles collide when the distance between their centers is
     * less than or equal to the sum of their radii.
     * 
     * Formula: collision = (radius_a + radius_b) >= distance_between_centers
     * Where: distance = sqrt((x2-x1)² + (y2-y1)²)
     */
    bool CheckCircullarCollision(int aRadius, int bRadius, glm::vec2 aPos, glm::vec2 bPos) {
        glm::vec2 dif = aPos - bPos;
        double length = glm::sqrt((dif.x * dif.x) + (dif.y * dif.y));
        // Hay colision si la suma entre radios >= a la distancia entre centros
        return (aRadius + bRadius) >= length;
    }
};

#endif // COLLISIONSYSTEM_HPP