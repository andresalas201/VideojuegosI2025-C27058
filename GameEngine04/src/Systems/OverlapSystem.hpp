#ifndef OVERLAPSYSTEM_HPP
#define OVERLAPSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"

#include "../Components/CameraFollowComponent.hpp"

enum Direction {top, left, bottom, right};

class OverlapSystem : public System {
    private:

        bool CheckCollision(Entity a, Entity b, Direction dir) {
            auto& aCollider = a.GetComponent<BoxColliderComponent>();
            auto& bCollider = b.GetComponent<BoxColliderComponent>();
            auto& aTransform = a.GetComponent<TransformComponent>();
            auto& bTransform = b.GetComponent<TransformComponent>();

            float aX = aTransform.previousPosition.x;
            float aY = aTransform.previousPosition.y;
            float aW = static_cast<float>(aCollider.width);
            float aH = static_cast<float>(aCollider.height);
            
            float bX = bTransform.previousPosition.x;
            float bY = bTransform.previousPosition.y;
            float bW = static_cast<float>(bCollider.width);
            float bH = static_cast<float>(bCollider.height);

            if (Direction::top == dir) {
                return {
                    aX < bX + bW &&
                    aX + aW > bX &&
                    aY > bY
                };
            } else if (Direction::bottom == dir) {
                return {
                    aX < bX + bW &&
                    aX + aW > bX &&
                    aY < bY
                };
            } else if (Direction::left == dir) {
                return {
                    aY < bY + bH &&
                    aY + aH > bY &&
                    aX > bX
                };
            } else {
                return {
                    aY < bY + bH &&
                    aY + aH > bY &&
                    aX < bX
                };
            } 
        }

        void AvoidOverlap(Entity a, Entity b) {
            auto& aCollider = a.GetComponent<BoxColliderComponent>();
            auto& aTransform = a.GetComponent<TransformComponent>();
            
            auto& bCollider = b.GetComponent<BoxColliderComponent>();
            auto& bTransform = b.GetComponent<TransformComponent>();
            auto& bRigidBody = b.GetComponent<RigidBodyComponent>();

            if(CheckCollision(a,b, Direction::top)) {
                bTransform.position = glm::vec2(bTransform.position.x, 
                    aTransform.position.y - bCollider.height);
                bRigidBody.velocity = glm::vec2(bRigidBody.velocity.x, 0.0f);
            }
            if(CheckCollision(a,b, Direction::bottom)) {
                bTransform.position = glm::vec2(bTransform.position.x, 
                    aTransform.position.y + aCollider.height);
                bRigidBody.velocity = glm::vec2(bRigidBody.velocity.x, 0.0f);
            }
            if (CheckCollision(a,b, Direction::left)) {
                bTransform.position = glm::vec2(aTransform.position.x - bCollider.width, 
                    bTransform.position.y);
                bRigidBody.velocity = glm::vec2(0.0f, bRigidBody.velocity.y);
            }
            if (CheckCollision(a,b, Direction::right)) {
                bTransform.position = glm::vec2(aTransform.position.x + aCollider.width, 
                    bTransform.position.y);
                bRigidBody.velocity = glm::vec2(0.0f, bRigidBody.velocity.y);
            }
        }
    
    public:
    
        OverlapSystem() {
            RequireComponent<RigidBodyComponent>();
            RequireComponent<BoxColliderComponent>();
            RequireComponent<TransformComponent>();
        }

        void SubscribeToCollisionEvent(const std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<CollisionEvent, OverlapSystem>(this,
                &OverlapSystem::OnCollisionEvent);
        }

        void OnCollisionEvent(CollisionEvent& e) {
            auto& aRigidBody = e.a.GetComponent<RigidBodyComponent>();
            auto& bRigidBody = e.b.GetComponent<RigidBodyComponent>();
            if(aRigidBody.isSolid && bRigidBody.isSolid) {
                if(aRigidBody.mass >= bRigidBody.mass) {
                    AvoidOverlap(e.a, e.b);
                } else {
                    AvoidOverlap(e.b, e.a);
                }
            }
        }
    
    

};

#endif // OVERLAPSYSTEM_HPP