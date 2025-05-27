#ifndef LEVELENDSYSTEM_HPP
#define LEVELENDSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../SceneManager/SceneManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/BossActivationEvent.hpp"
#include "../Components/PlayerComponent.hpp"
#include "../Components/BossComponent.hpp"

class LevelEndSystem : public System {
    private:
        bool bossSpawned;

        void WinLevel(std::unique_ptr<Registry>& registry,
            std::unique_ptr<SceneManager>& sceneManager) {

            sceneManager->SetNextScene(registry->winScene);
            sceneManager->StopScene();

        }
        
        void LoseLevel (std::unique_ptr<Registry>& registry,
            std::unique_ptr<SceneManager>& sceneManager) {

            sceneManager->SetNextScene(registry->loseScene);
            sceneManager->StopScene();
        }


    public:
        LevelEndSystem() {
        }

        void Reset() {
            this->bossSpawned = false;
        }

        void SubscribeToBossActivation(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<BossActivationEvent, LevelEndSystem>(this, 
                &LevelEndSystem::OnBossActivation);
        }

        void Update(std::unique_ptr<Registry>& registry,
            std::unique_ptr<SceneManager>& sceneManager) {
            bool playerExists = false;
            bool bossExists = false;
            for (auto entity : GetSystemEntities()) {
                if (entity.HasComponent<BossComponent>()) bossExists = true;
                if (entity.HasComponent<PlayerComponent>()) {
                    playerExists = true;
                    break;
                }
            }
            if (this->bossSpawned && !bossExists) {
                WinLevel(registry, sceneManager);
                return;
            }
            if (!playerExists) LoseLevel(registry, sceneManager);
        }

        void OnBossActivation(BossActivationEvent& e) {
            this->bossSpawned = e.isActive;
        }
};


#endif // LEVELENDSYSTEM_HPP