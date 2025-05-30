/**
 * @file ScoreSystem.hpp
 * @brief Header file for the ScoreSystem class
 */

#ifndef SCORESYSTEM_HPP
#define SCORESYSTEM_HPP
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/DeathEvent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/ScoreComponent.hpp"
#include "../Components/EnemyComponent.hpp"

/**
 * @class ScoreSystem
 * @brief System responsible for managing player score and boss spawning logic
 * 
 * This system handles score tracking, updates score display text, and triggers
 * boss spawn events when certain score thresholds are reached. It listens to
 * death events to increment the score when enemies are defeated.
 */
class ScoreSystem : public System {
private:
    int Score;        ///< Current player score
    int startScore;   ///< Score at the start of the current level/session
    bool bossSpawned; ///< Flag indicating whether boss has been spawned
    
    /**
     * @brief Sends a boss spawn event when score threshold is reached
     * 
     * @param eventManager Reference to the event manager for emitting events
     * @param a Reference to the entity that triggered the spawn condition
     */
    void SendSpawnEvent(std::unique_ptr<EventManager>& eventManager, Entity& a) {
        std::cout << "[SCORESYSTEM] Se alcanzan los puntos para el jefe\n";
        eventManager->EmitEvent<BossSpawnEvent>(a);
    }
    
public:
    /**
     * @brief Constructor for ScoreSystem
     * 
     * Sets up the system to require TextComponent and ScoreComponent
     * for entities to be processed, and initializes the score to 0.
     */
    ScoreSystem() {
        RequireComponent<TextComponent>();
        RequireComponent<ScoreComponent>();
        this->Score = 0;
    }
    
    /**
     * @brief Sets the starting score for boss spawn calculations
     * 
     * Records the current score as the baseline for determining when
     * to spawn a boss, and resets the boss spawned flag.
     */
    void SetStartScore () {
        this->startScore = Score;
        this->bossSpawned = false;
    }
    
    /**
     * @brief Resets the score to zero
     */
    void Reset() {
        this->Score = 0;
    }
    
    /**
     * @brief Updates score display and checks for boss spawn conditions
     * 
     * Updates the text component of score entities to display current score,
     * and triggers boss spawn event if the score threshold has been reached
     * and a boss hasn't been spawned yet.
     * 
     * @param eventManager Reference to the event manager for emitting events
     */
    void Update(std::unique_ptr<EventManager>& eventManager) {
        for (auto& entity : GetSystemEntities()) {
            Entity& a = entity;
            auto& text = a.GetComponent<TextComponent>();
            auto& score = a.GetComponent<ScoreComponent>();
            text.text = "Score: " + std::to_string(this->Score);
            if (!this->bossSpawned && score.bossScore < (this->Score - this->startScore)) {
                SendSpawnEvent(eventManager, a);
                this->bossSpawned = true;
            }
        }
    }
    
    /**
     * @brief Subscribes to death events to track enemy defeats
     * 
     * Sets up event listening for DeathEvent to automatically update
     * the score when enemies are destroyed.
     * 
     * @param eventManager Reference to the event manager for subscription
     */
    void SubscribeToDeathEvent(std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<DeathEvent, ScoreSystem>(this, &ScoreSystem::CheckDeath);
    }
    
    /**
     * @brief Event handler for death events
     * 
     * Checks if the deceased entity is an enemy and adds its score value
     * to the total score if so.
     * 
     * @param e Reference to the DeathEvent containing the deceased entity
     */
    void CheckDeath(DeathEvent& e) {
        if (e.a.HasComponent<EnemyComponent>()) {
            this->Score += e.a.GetComponent<EnemyComponent>().score;
        }
    }
};
#endif // SCORESYSTEM_HPP