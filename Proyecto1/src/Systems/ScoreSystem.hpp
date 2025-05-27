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
    public:

        ScoreSystem() {
            RequireComponent<TextComponent>();
            RequireComponent<ScoreComponent>();
            this->Score = 0;
        }

        void Update() {
            for (auto& entity : GetSystemEntities()) {
                Entity& a = entity;
                auto& text = a.GetComponent<TextComponent>();
                text.text = "Score: " + std::to_string(this->Score);
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