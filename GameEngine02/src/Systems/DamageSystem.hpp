#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <memory>

#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class DamageSystem : public System {

    public:
        DamageSystem() {
            RequireComponent<CircleColliderComponent>();
        }

        void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this,
                &DamageSystem::OnCollision);
        }

        void OnCollision(CollisionEvent& e) {
            std::cout << "[DAMAGESYSTEM] Colision de entidad " << e.a.GetId() << " y " << e.b.GetId() << std::endl;
            e.a.Kill();
            e.b.Kill();
        }
};

#endif // DAMAGESYSTEM_HPP