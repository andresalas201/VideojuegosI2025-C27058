/**
 * @file LevelEndSystem.hpp
 * @brief Level end condition system implementation for ECS architecture
 */

#ifndef LEVELENDSYSTEM_HPP
#define LEVELENDSYSTEM_HPP
#include "../ECS/ECS.hpp"
#include "../SceneManager/SceneManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/BossActivationEvent.hpp"
#include "../Components/PlayerComponent.hpp"
#include "../Components/BossComponent.hpp"

/**
 * @class LevelEndSystem
 * @brief System responsible for detecting and handling level completion conditions
 * 
 * This system monitors game state to determine when a level should end, either
 * through victory (boss defeated) or defeat (no players remaining). It manages
 * scene transitions and responds to boss activation events.
 */
class LevelEndSystem : public System {
private:
    /** @brief Flag indicating whether a boss has been spawned in the current level */
    bool bossSpawned;

    /**
     * @brief Handles level victory conditions
     * 
     * @param registry Reference to the game registry
     * @param sceneManager Reference to the scene manager
     * 
     * Transitions to the win scene and stops the current scene when the level is won.
     */
    void WinLevel(std::unique_ptr<Registry>& registry,
    std::unique_ptr<SceneManager>& sceneManager) {
        std::cout << "[LEVELENDSYSTEM] Se gana el nivel\n";
        sceneManager->SetNextScene(registry->winScene);
        sceneManager->StopScene();
    }

    /**
     * @brief Handles level defeat conditions
     * 
     * @param registry Reference to the game registry
     * @param sceneManager Reference to the scene manager
     * 
     * Transitions to the lose scene and stops the current scene when the level is lost.
     */
    void LoseLevel (std::unique_ptr<Registry>& registry,
    std::unique_ptr<SceneManager>& sceneManager) {
        sceneManager->SetNextScene(registry->loseScene);
        sceneManager->StopScene();
        std::cout << "[LEVELENDSYSTEM] Se pierde el nivel\n";
    }

public:
    /**
     * @brief Constructor for LevelEndSystem
     * 
     * Initializes the level end system without requiring specific components.
     */
    LevelEndSystem() {
    }

    /**
     * @brief Resets the system state for a new level
     * 
     * Resets the boss spawned flag to false for level initialization.
     */
    void Reset() {
        this->bossSpawned = false;
    }

    /**
     * @brief Subscribes to boss activation events
     * 
     * @param eventManager Reference to the event manager
     * 
     * Sets up event subscription to receive notifications when bosses are activated.
     */
    void SubscribeToBossActivation(std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<BossActivationEvent, LevelEndSystem>(this,
        &LevelEndSystem::OnBossActivation);
    }

    /**
     * @brief Updates the system and checks for level end conditions
     * 
     * @param registry Reference to the game registry
     * @param sceneManager Reference to the scene manager
     * @return bool True if the level should end due to defeat, false otherwise
     * 
     * Monitors the existence of player and boss entities to determine level state.
     * Triggers win condition when boss is defeated, lose condition when no players remain.
     */
    bool Update(std::unique_ptr<Registry>& registry,
    std::unique_ptr<SceneManager>& sceneManager) {
        bool playerExists = false;
        bool bossExists = false;
        for (auto entity : GetSystemEntities()) {
            if (entity.HasComponent<BossComponent>()) bossExists = true;
            if (entity.HasComponent<PlayerComponent>()) {
                playerExists = true;
            }
        }
        if (this->bossSpawned && !bossExists) {
            WinLevel(registry, sceneManager);
            return false;
        }
        if (!playerExists) {
            LoseLevel(registry, sceneManager);
            return true;
        }
        return false;
    }

    /**
     * @brief Event handler for boss activation events
     * 
     * @param e Reference to the boss activation event
     * 
     * Updates the boss spawned flag when a boss activation event is received.
     */
    void OnBossActivation(BossActivationEvent& e) {
        std::cout << "[LEVELENDSYSTEM] Jefe activado\n";
        this->bossSpawned = e.isActive;
    }
};
#endif // LEVELENDSYSTEM_HPP