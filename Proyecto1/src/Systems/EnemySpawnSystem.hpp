#ifndef ENEMYSPAWNSYSTEM_HPP
#define ENEMYSPAWNSYSTEM_HPP

#include <memory>
#include <time.h>
#include "../ECS/ECS.hpp"
#include "../PreEntity/PreEntity.hpp"

class EnemySpawnSystem : public System {
    private:
        Uint32 waitBetween;
        Uint32 lastSpawn;
        int width;
        int height;
        int currentGroup;

        int GenerateY() {
            return rand() % height;
        }
        
        void AddSpawnGroup (std::unique_ptr<Registry>& registry) {
            
            int index = rand() % registry->enemyVector.size();
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


    public:
        EnemySpawnSystem() {
            srand(time(NULL));
            this->lastSpawn = 0;
            this->currentGroup = 0;
        }

        void SetParameter(int waitBetweenSpawn, int width, int height) {
            this->waitBetween = waitBetweenSpawn;
            this->width = width;
            this->height = height;
        }

        void Update(std::unique_ptr<Registry>& registry) {
            if (((SDL_GetTicks() - lastSpawn) / 1000) > waitBetween) {
                AddSpawnGroup(registry);
            }
            SpawnEnemy(registry);
        }

};

#endif // ENEMYSPAWNSYSTEM_HPP