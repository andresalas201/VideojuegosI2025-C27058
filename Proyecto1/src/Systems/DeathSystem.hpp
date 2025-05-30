/**
 * @file DeathSystem.hpp
 * @brief Defines the DeathSystem class for handling entity death processing and cleanup
 */

#ifndef DEATHSYSTEM_HPP
#define DEATHSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/PlayerComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/DeathEvent.hpp"
#include "../Components/EnemyComponent.hpp"
#include "../Events/GroupDeathEvent.hpp"
#include "AudioSystem.hpp"

/**
 * @class DeathSystem
 * @brief System responsible for processing entity deaths and managing death animations
 * 
 * The DeathSystem handles the death process of entities, including playing death animations,
 * managing death timers, playing death sounds, and performing cleanup operations. It processes
 * both immediate deaths (shots, upgrades) and delayed deaths with visual effects (sprites).
 * The system also handles special cases like player deaths and group enemy management.
 */
class DeathSystem : public System {
public:
    /**
     * @brief Constructor that sets up required components for the death system
     * 
     * Requires entities to have both SpriteComponent and TransformComponent
     * to be processed by this system for death animations and positioning.
     */
    DeathSystem() {
        RequireComponent<SpriteComponent>();
        RequireComponent<TransformComponent>();
    }

    /**
     * @brief Subscribes the death system to death events
     * @param eventManager Unique pointer to the event manager
     * 
     * Registers the OnDeath method to be called whenever a DeathEvent occurs,
     * allowing the system to respond to entity deaths throughout the game.
     */
    void SubscribeToDeathEvent(std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<DeathEvent, DeathSystem>(this, &DeathSystem::OnDeath);
    }

    /**
     * @brief Updates the death system and processes dying entities
     * @param MILISECS_PER_FRAME Milliseconds per frame for timing calculations
     * @param FPS Frames per second for timing calculations
     * @param windowHeight Height of the game window for player boundary checking
     * @param eventManager Unique pointer to the event manager for emitting events
     * 
     * Processes entities that are marked as dead:
     * - For players: Kills them when they fall below the window boundary
     * - For other entities: Waits for death animation duration before cleanup
     * - For enemies: Emits GroupDeathEvent when the last enemy in a group dies
     */
    void Update(int MILISECS_PER_FRAME, int FPS, int windowHeight,
                std::unique_ptr<EventManager>& eventManager) {
        Uint32 maxTime = MILISECS_PER_FRAME * FPS * 0.5; // Death animation duration (0.5 seconds)
        
        for (auto& entity : GetSystemEntities()) {
            Entity& a = entity;
            if(a.GetComponent<SpriteComponent>().isDead) {
                auto sprite = a.GetComponent<SpriteComponent>();
                
                // Handle player death - kill when falling off screen
                if (a.HasComponent<PlayerComponent>()) {
                    if (a.GetComponent<TransformComponent>().position.y > windowHeight) {
                        std::cout << "[DEATHSYSTEM] Jugador " <<
                            a.GetComponent<PlayerComponent>().playerNumber << " ha muerto\n";
                        a.Kill();
                    }
                } 
                // Handle other entities - wait for death animation to complete
                else if ((SDL_GetTicks() - sprite.deathTime) > maxTime) {
                    // Check if this is the last enemy in a group
                    if (a.HasComponent<EnemyComponent>() &&
                        a.GetComponent<EnemyComponent>().fatherGroup->groupLeft <= 0) {
                        eventManager->EmitEvent<GroupDeathEvent>(a);
                    }
                    a.Kill();
                }
            }
        }
    }

    /**
     * @brief Handles death events for entities
     * @param e Reference to the DeathEvent containing the dying entity
     * 
     * Processes entity death by:
     * - Playing death sounds if the entity has a SoundComponent
     * - Immediately killing shots and upgrades (no death animation needed)
     * - Managing shot counters for entities with fathers
     * - Setting up death animations for sprite entities
     * - Disabling colliders for dead entities
     * - Decrementing group counters for enemy entities
     */
    void OnDeath(DeathEvent& e) {
        std::cout << "[DEATHSYSTEM] Se muere la entidad " << e.a.GetId() << std::endl;
        
        // Play death sound if available
        if(e.a.HasComponent<SoundComponent>()) {
            std::string soundPath = e.a.GetComponent<SoundComponent>().soundName;
            e.a.registry->GetSystem<AudioSystem>().playSound(
                Game::GetInstance().assetManager->GetSound(soundPath));
        }

        // Handle immediate death for shots and upgrades (no animation needed)
        if(e.a.HasComponent<ShotComponent>() || e.a.HasComponent<UpgradeComponent>()) {
            // Decrement shot counter if entity has a father
            if (e.a.HasComponent<FatherComponent>()) {
                auto& father = e.a.GetComponent<FatherComponent>();
                if(father.father->currentShots) father.father->currentShots--;
            }
            e.a.Kill();
            return;
        }

        // Set up death animation for sprite entities
        if (e.a.HasComponent<SpriteComponent>()) {
            auto& sprite = e.a.GetComponent<SpriteComponent>();
            sprite.isDead = true;
            sprite.deathTime = SDL_GetTicks();
        }

        // Disable collider for dead entity
        if (e.a.HasComponent<CircleColliderComponent>()) {
            auto& collider = e.a.GetComponent<CircleColliderComponent>();
            collider.isDead = true;
        }

        // Decrement group counter for enemy entities
        if (e.a.HasComponent<EnemyComponent>()) {
            e.a.GetComponent<EnemyComponent>().fatherGroup->groupLeft--;
        }
    }
};

#endif // DEATHSYSTEM_HPP