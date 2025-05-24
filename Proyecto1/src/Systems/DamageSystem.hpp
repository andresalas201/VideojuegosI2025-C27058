#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <memory>

#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/ShotComponent.hpp"
#include "../Components/SoundComponent.hpp"
#include "../Components/UpgradeComponent.hpp"
#include "../Components/PlayerComponent.hpp"
#include "../Components/AttackComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"
#include "../Events/DeathEvent.hpp"
#include "AudioSystem.hpp"

class DamageSystem : public System {

    public:

        void SetDamageWait(int FPS, int MILISECS_PER_FRAME, int seconds) {
            this->damageWait = FPS * MILISECS_PER_FRAME * seconds;
        }

        DamageSystem() {
            RequireComponent<CircleColliderComponent>();
            RequireComponent<HealthComponent>();
        }

        void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this,
                &DamageSystem::OnCollision);
        }

        void Update(std::unique_ptr<EventManager>& eventManager) {
            auto entities = GetSystemEntities();

            for (auto i = entities.begin(); i != entities.end(); i++) {
                Entity a = *i;
                if(a.GetComponent<HealthComponent>().health <= 0 &&
                    !a.GetComponent<CircleColliderComponent>().isDead) {
                    eventManager->EmitEvent<DeathEvent>(a);
                }
            }
            
        }

        void OnCollision(CollisionEvent& e) {
            std::cout << "[DAMAGESYSTEM] Colision de entidad " << e.a.GetId() << " y " << e.b.GetId() << std::endl;
            if (e.a.HasComponent<PlayerComponent>() && e.b.HasComponent<UpgradeComponent>()) {
                Upgrade(e.a, e.b.GetComponent<UpgradeComponent>().increase);
                e.b.GetComponent<HealthComponent>().health = 0;
                return;
            }
            if (e.a.HasComponent<SpriteComponent>()) {
                e.a.GetComponent<SpriteComponent>().isHit = true;
                e.a.GetComponent<SpriteComponent>().hitTime = SDL_GetTicks();
                e.a.GetComponent<SpriteComponent>().showHitCounter = 0;
            }
            if (e.b.HasComponent<SpriteComponent>()) {
                e.b.GetComponent<SpriteComponent>().isHit = true;
                e.b.GetComponent<SpriteComponent>().hitTime = SDL_GetTicks();
                e.a.GetComponent<SpriteComponent>().showHitCounter = 0;
            }
            if ((SDL_GetTicks() - e.a.GetComponent<HealthComponent>().lastHit) > damageWait) {
                e.a.GetComponent<HealthComponent>().health -= e.b.GetComponent<HealthComponent>().damage;
                auto& healthA = e.a.GetComponent<HealthComponent>();
                healthA.lastHit = SDL_GetTicks();
            }
            if ((SDL_GetTicks() - e.b.GetComponent<HealthComponent>().lastHit) > damageWait) {
                e.b.GetComponent<HealthComponent>().health -= e.a.GetComponent<HealthComponent>().damage; 
                auto& healthB = e.b.GetComponent<HealthComponent>();
                healthB.lastHit = SDL_GetTicks();
            }
        }

    private:

        Uint32 damageWait;
        

        void Upgrade(Entity upgraded, int increase) {
            // TODO(any): annadir un upgrade que annada tiros dobles y triples
            if(!upgraded.HasComponent<AttackComponent>()) return;
            upgraded.GetComponent<AttackComponent>().damage += increase;
            std::cout << "Entity " << upgraded.GetId() << " aumenta su daño por " << increase <<
                " a " << upgraded.GetComponent<AttackComponent>().damage << std::endl;
        }
};

#endif // DAMAGESYSTEM_HPP