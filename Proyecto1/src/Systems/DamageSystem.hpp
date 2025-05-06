#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <memory>

#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class DamageSystem : public System {

    public:
        DamageSystem() {
            RequireComponent<CircleColliderComponent>();
            RequireComponent<HealthComponent>();
        }

        void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this,
                &DamageSystem::OnCollision);
        }

        void OnCollision(CollisionEvent& e) {
            std::cout << "[DAMAGESYSTEM] Colision de entidad " << e.a.GetId() << " y " << e.b.GetId() << std::endl;
            e.a.GetComponent<HealthComponent>().health -= e.b.GetComponent<HealthComponent>().damage;
            e.b.GetComponent<HealthComponent>().health -= e.a.GetComponent<HealthComponent>().damage; 
            if(e.a.GetComponent<HealthComponent>().health <= 0) {
                this->eventManager->EmitEvent<DeathEvent>(e.a); 
                e.a.Kill();
            }
            if(e.b.GetComponent<HealthComponent>().health <= 0) {
                this->eventManager->EmitEvent<DeathEvent>(e.a);
                e.b.Kill();
            }
        }
    private:
        std::unique_ptr<EventManager>& eventManager;
};

#endif // DAMAGESYSTEM_HPP