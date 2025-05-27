#ifndef ENEMYSPAWNSYSTEM_HPP
#define ENEMYSPAWNSYSTEM_HPP

#include <memory>
#include <time.h>
#include <vector>
#include "../ECS/ECS.hpp"
#include "../PreEntity/PreEntity.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/BossSpawnEvent.hpp"
#include "../Events/BossActivationEvent.hpp"

class EnemySpawnSystem : public System {
    private:
        Uint32 waitBetween;
        Uint32 lastSpawn;
        int width;
        int height;
        int currentGroup;
        bool bossSpawned;
        bool bossReady;
        std::vector<PreEntity> bosses;

        int GenerateY() {
            return rand() % height;
        }
        
        void AddSpawnGroup (std::unique_ptr<Registry>& registry) {
            
            int index = rand() % registry->enemyVector.size();
            int tries = 0;
            while (registry->enemyVector[index].isBoss && tries < 10) {
                index = (index + 1) % registry->enemyVector.size();
                tries++;
            }
            if (tries >= 10) return;
            PreEntity newEnemyGroup = registry->enemyVector[index];
            newEnemyGroup.SetSpawn(width+5, GenerateY());
            int baseGroupNumber = newEnemyGroup.groupNumber;
            newEnemyGroup.groupNumber = currentGroup;
            this->currentGroup++;
            registry->enemiesToSpawn.push_back(newEnemyGroup);
            this->lastSpawn = SDL_GetTicks();
            std::cout << "[ENEMYSPAWNSYSTEM] Se agrega el grupo " << newEnemyGroup.groupNumber <<
                " apartir de " << baseGroupNumber << std::endl;
        }

        void SpawnEnemy(std::unique_ptr<Registry>& registry) {
            for (long unsigned int i = 0; i < registry->enemiesToSpawn.size(); i++) {
                if(registry->enemiesToSpawn[i].spawnedAmount >= 
                    registry->enemiesToSpawn[i].spawnMax) continue;
                if((SDL_GetTicks() - registry->enemiesToSpawn[i].lastSpawnTick)/1000 > 
                    static_cast<Uint32>(registry->enemiesToSpawn[i].spawnWait)) {
                    std::cout << "[ENEMYSPAWNSYSTEM] Se spawnea del grupo " << i << std::endl;
                    registry->enemiesToSpawn[i].CreateEntity(registry);
                    registry->enemiesToSpawn[i].spawnedAmount ++;
                }
            }
        }

        void PrepareBossEntity(PreEntity boss) {
            int x = this->width - boss.bossX;
            int y = boss.bossY;
            boss.SetSpawn(x, y);
            this->bosses.push_back(boss);
        }

        void SpawnBoss(std::unique_ptr<Registry>& registry) {
            for (long unsigned int i = 0; i < bosses.size(); i++) {
                bosses[i].CreateEntity(registry);
            }
            this->bossSpawned = true;
            bosses.clear();
        }


    public:
        EnemySpawnSystem() {
            srand(time(NULL));
            this->lastSpawn = 0;
            this->currentGroup = 0;
            this->bossReady = false;
            this->bossSpawned = false;
        }

        void Reset() {
            this->lastSpawn = SDL_GetTicks();
            this->currentGroup = 0;
            this->bossReady = false;
            this->bossSpawned = false;
        }

        void SetParameter(int waitBetweenSpawn, int width, int height) {
            this->waitBetween = waitBetweenSpawn;
            this->width = width;
            this->height = height;
        }

        void SubscribeToBossSpawnEvent(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<BossSpawnEvent, EnemySpawnSystem>(this,
            &EnemySpawnSystem::OnBossSpawn);
        }

        void Update(std::unique_ptr<Registry>& registry, std::unique_ptr<EventManager>& eventManager) {
            if (!this->bossSpawned) {
                if (this->bossReady) {
                    SpawnBoss(registry);
                    eventManager->EmitEvent<BossActivationEvent>();  
                    return;
                }
                if (((SDL_GetTicks() - lastSpawn) / 1000) > waitBetween) {
                    AddSpawnGroup(registry);
                }
                SpawnEnemy(registry);
            }
        }

        void OnBossSpawn(BossSpawnEvent& e) {
            Registry* registry = e.a.registry;
            for (long unsigned int i = 0; i < registry->enemyVector.size(); i++) {
                if (registry->enemyVector[i].isBoss) {
                    PrepareBossEntity(registry->enemyVector[i]);
                }
            }
            this->bossReady = true;
        }

};

#endif // ENEMYSPAWNSYSTEM_HPP