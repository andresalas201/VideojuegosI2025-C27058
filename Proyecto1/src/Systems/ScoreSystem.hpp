#ifndef SCORESYSTEM_HPP
#define SCORESYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/DeathEvent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/ScoreComponent.hpp"
#include "../Components/EnemyComponent.hpp"

class ScoreSystem : public System {
    private:
        int Score;
        int startScore;
        bool bossSpawned;

        void SendSpawnEvent(std::unique_ptr<EventManager>& eventManager, Entity& a) {
            std::cout << "[SCORESYSTEM] Se alcanzan los puntos para el jefe\n";
            eventManager->EmitEvent<BossSpawnEvent>(a);
        }

    public:

        ScoreSystem() {
            RequireComponent<TextComponent>();
            RequireComponent<ScoreComponent>();
            this->Score = 0;
        }

        void SetStartScore () {
            this->startScore = Score;
            this->bossSpawned = false;
        }

        void Reset() {
            this->Score = 0;
        }

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

        void SubscribeToDeathEvent(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<DeathEvent, ScoreSystem>(this, &ScoreSystem::CheckDeath);
        }

        void CheckDeath(DeathEvent& e) {
            if (e.a.HasComponent<EnemyComponent>()) {
                this->Score += e.a.GetComponent<EnemyComponent>().score;
            }
        }
};

#endif // SCORESYSTEM_HPP