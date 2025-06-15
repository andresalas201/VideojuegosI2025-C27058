#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include "../ECS/ECS.hpp"

#include "../Components/RigidBodyComponent.hpp"

class PhysicsSystem : public System {

    public:
        PhysicsSystem() {
            RequireComponent<RigidBodyComponent>();
        }

        void Update() {
            for (auto entity : GetSystemEntities()) {
                auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
                
                // Aplicar fuerza de gravedad
                if (rigidBody.isDynamic) {
                    rigidBody.sumForces += glm::vec2(0.0f, 9.8 * rigidBody.mass * 64);
                }
            }
        }
};


#endif // PHYSICSSYSTEM_HPP