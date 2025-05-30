/**
 * @file EnemySpawnSystem.hpp
 * @brief Defines the EnemySpawnSystem class for managing enemy spawning and boss encounters
 */

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

/**
 * @class EnemySpawnSystem
 * @brief System responsible for spawning enemy groups and managing boss encounters
 * 
 * The EnemySpawnSystem handles the spawning of enemy entities in groups at timed intervals.
 * It manages the creation of enemy waves, boss preparation and spawning, and maintains
 * timing controls for balanced gameplay. The system can transition between regular enemy
 * spawning and boss encounter modes.
 */
class EnemySpawnSystem : public System {
    private:
        /**
         * @brief Time in milliseconds to wait between enemy group spawns
         */
        Uint32 waitBetween;
        
        /**
         * @brief Timestamp of the last enemy group spawn
         */
        Uint32 lastSpawn;
        
        /**
         * @brief Width of the spawn area
         */
        int width;
        
        /**
         * @brief Height of the spawn area
         */
        int height;
        
        /**
         * @brief Current group number counter for spawned enemy groups
         */
        int currentGroup;
        
        /**
         * @brief Flag indicating if a boss has been spawned
         */
        bool bossSpawned;
        
        /**
         * @brief Flag indicating if boss entities are ready to spawn
         */
        bool bossReady;
        
        /**
         * @brief Vector containing prepared boss entities ready for spawning
         */
        std::vector<PreEntity> bosses;

        /**
         * @brief Generates a random Y coordinate within the spawn area
         * @return Random Y coordinate for enemy spawn position
         */
        int GenerateY() {
            return rand() % height;
        }
        
        /**
         * @brief Adds a new enemy group to the spawn queue
         * @param registry Unique pointer to the entity registry
         * 
         * Selects a random non-boss enemy type from the registry, assigns it a new
         * group number, sets its spawn position, and adds it to the spawn queue.
         */
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

        /**
         * @brief Spawns individual enemies from queued enemy groups
         * @param registry Unique pointer to the entity registry
         * 
         * Iterates through all queued enemy groups and spawns individual enemies
         * based on their spawn timing and maximum spawn count constraints.
         */
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

        /**
         * @brief Prepares a boss entity for spawning
         * @param boss PreEntity representing the boss to prepare
         * 
         * Sets the boss spawn position based on its configured coordinates
         * and adds it to the bosses vector for later spawning.
         */
        void PrepareBossEntity(PreEntity boss) {
            int x = this->width - boss.bossX;
            int y = boss.bossY;
            boss.SetSpawn(x, y);
            this->bosses.push_back(boss);
        }

        /**
         * @brief Spawns all prepared boss entities
         * @param registry Unique pointer to the entity registry
         * 
         * Creates all boss entities that have been prepared, marks boss as spawned,
         * and clears the boss preparation vector.
         */
        void SpawnBoss(std::unique_ptr<Registry>& registry) {
            for (long unsigned int i = 0; i < bosses.size(); i++) {
                bosses[i].CreateEntity(registry);
            }
            this->bossSpawned = true;
            bosses.clear();
        }


    public:
        /**
         * @brief Constructor that initializes the enemy spawn system
         * 
         * Seeds the random number generator and initializes all timing
         * and state variables to their default values.
         */
        EnemySpawnSystem() {
            srand(time(NULL));
            this->lastSpawn = 0;
            this->currentGroup = 0;
            this->bossReady = false;
            this->bossSpawned = false;
        }

        /**
         * @brief Resets the spawn system to initial state
         * 
         * Resets all timing counters and state flags, typically used
         * when starting a new level or game session.
         */
        void Reset() {
            this->lastSpawn = SDL_GetTicks();
            this->currentGroup = 0;
            this->bossReady = false;
            this->bossSpawned = false;
        }

        /**
         * @brief Sets spawn system parameters
         * @param waitBetweenSpawn Time in seconds to wait between enemy group spawns
         * @param width Width of the spawn area
         * @param height Height of the spawn area
         */
        void SetParameter(int waitBetweenSpawn, int width, int height) {
            this->waitBetween = waitBetweenSpawn;
            this->width = width;
            this->height = height;
        }

        /**
         * @brief Subscribes the spawn system to boss spawn events
         * @param eventManager Unique pointer to the event manager
         * 
         * Registers the OnBossSpawn method to be called when BossSpawnEvent occurs.
         */
        void SubscribeToBossSpawnEvent(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<BossSpawnEvent, EnemySpawnSystem>(this,
            &EnemySpawnSystem::OnBossSpawn);
        }

        /**
         * @brief Updates the enemy spawn system
         * @param registry Unique pointer to the entity registry
         * @param eventManager Unique pointer to the event manager
         * 
         * Main update loop that handles:
         * - Boss spawning when ready
         * - Regular enemy group spawning based on timing
         * - Individual enemy spawning from queued groups
         * Only operates when enemies are available and no boss is active.
         */
        void Update(std::unique_ptr<Registry>& registry, std::unique_ptr<EventManager>& eventManager) {
            if (registry->enemyVector.empty()) return;
            if (!this->bossSpawned) {
                if (this->bossReady) {
                    SpawnBoss(registry);
                    this->bossReady = false;
                    eventManager->EmitEvent<BossActivationEvent>();  
                    return;
                }
                if (((SDL_GetTicks() - lastSpawn) / 1000) > waitBetween) {
                    AddSpawnGroup(registry);
                }
                SpawnEnemy(registry);
            }
        }

        /**
         * @brief Handles boss spawn events
         * @param e Reference to the BossSpawnEvent
         * 
         * Prepares all boss entities from the registry for spawning by
         * setting their positions and marking the system as boss ready.
         */
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