/**
 * @file DamageSystem.hpp
 * @brief Defines the DamageSystem class for handling entity damage and death in collision events
 */

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

/**
 * @class DamageSystem
 * @brief System responsible for handling damage calculations and entity death detection
 * 
 * The DamageSystem processes collision events between entities and applies damage based on
 * their health components. It also monitors entity health and emits death events when
 * entities reach zero health. The system implements a damage cooldown mechanism to prevent
 * continuous damage application and handles upgrade collection for players.
 */
class DamageSystem : public System {
    public:
        /**
         * @brief Sets the damage wait time between damage applications
         * @param FPS Frames per second of the game
         * @param MILISECS_PER_FRAME Milliseconds per frame
         * @param seconds Number of seconds to wait between damage applications
         */
        void SetDamageWait(int FPS, int MILISECS_PER_FRAME, int seconds) {
            this->damageWait = FPS * MILISECS_PER_FRAME * seconds;
        }
        /**
         * @brief Constructor that sets up required components for the damage system
         */
        DamageSystem() {
            RequireComponent<CircleColliderComponent>();
            RequireComponent<HealthComponent>();
        }
        /**
         * @brief Subscribes the damage system to collision events
         * @param eventManager Unique pointer to the event manager
         */
        void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this,
            &DamageSystem::OnCollision);
        }
        /**
         * @brief Updates the damage system and checks for entity deaths
         * @param eventManager Unique pointer to the event manager
         */
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
        /**
         * @brief Handles collision events between entities
         * @param e Reference to the CollisionEvent containing the colliding entities
         */
        void OnCollision(CollisionEvent& e) {
            std::cout << "[DAMAGESYSTEM] Colision de entidad " << e.a.GetId() << " y " << e.b.GetId() << std::endl;
            if (e.a.HasComponent<PlayerComponent>() && e.b.HasComponent<UpgradeComponent>()) {
                if(e.b.GetComponent<UpgradeComponent>().upgrade.valid()) {
                    e.b.GetComponent<UpgradeComponent>().upgrade(e.a,
                    e.b.GetComponent<UpgradeComponent>().increase);
                }
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
        /**
         * @brief Time in milliseconds to wait between damage applications
         */
        Uint32 damageWait;
};
#endif // DAMAGESYSTEM_HPP