#ifndef BOXCOLLISIONSYSTEM_HPP
#define BOXCOLLISIONSYSTEM_HPP

#include <iostream>

#include "../ECS/ECS.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"

class BoxCollisionSystem : public System {
    private:

    bool CheckAABBCollision(float aX, float aY, float aW, float aH,
        float bX, float bY, float bW, float bH) {

        return {
            aX < bX + bW &&
            aX + aW > bX &&
            aY < bY + bH &&
            aY + aH > bY};
    }

    public:
        BoxCollisionSystem() {
            RequireComponent<BoxColliderComponent>();
            RequireComponent<TransformComponent>();
        }

        void Update() {
            auto entities = GetSystemEntities();

                for (auto i = entities.begin(); i != entities.end(); i++) {
                    Entity a = *i;
                    const auto& aCollider = a.GetComponent<BoxColliderComponent>();
                    const auto& aTransform = a.GetComponent<TransformComponent>();
                
                    for (auto j = i; j!= entities.end(); j++) {
                        Entity b = *j;

                        if (a == b) {
                            continue;
                        }
                        const auto& bCollider = b.GetComponent<BoxColliderComponent>();
                        const auto& bTransform = b.GetComponent<TransformComponent>();

                        bool collision = CheckAABBCollision(
                            aTransform.position.x, aTransform.position.y,
                            static_cast<float>(aCollider.width), 
                            static_cast<float>(aCollider.height),
                            bTransform.position.x, bTransform.position.y,
                            static_cast<float>(bCollider.width), 
                            static_cast<float>(bCollider.height));

                        if (collision) {
                            std::cout << a.GetId() << " colisiona con " << b.GetId() << std::endl;
                        }

                    }
                
                }
        }
};

#endif // BOXCOLLISIONSYSTEM_HPP