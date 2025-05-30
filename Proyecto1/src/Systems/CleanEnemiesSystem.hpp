/**
 * @file CleanEnemiesSystem.hpp
 * @brief System for cleaning up enemy entities that are no longer needed
 */

#ifndef CLEANENEMIESSYSTEM_HPP
#define CLEANENEMIESSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/EnemyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"

/**
 * @brief System responsible for cleaning up enemy entities and their spawn groups
 * 
 * The CleanEnemiesSystem manages the lifecycle of enemy entities by removing
 * those that have moved outside the visible screen area and cleaning up
 * empty enemy spawn groups from the registry. This helps maintain performance
 * by preventing accumulation of inactive enemies and unused spawn data.
 */
class CleanEnemiesSystem : public System {
private:
    int height; ///< Screen height for boundary checking
    int width;  ///< Screen width for boundary checking

    /**
     * @brief Removes empty enemy spawn groups from the registry
     * @param registry Reference to the game registry containing enemy spawn data
     * 
     * Iterates through all enemy spawn groups in the registry and removes
     * groups that no longer have any active entities. This prevents memory
     * accumulation of obsolete spawn group data.
     */
    void CleanEnemyGroups(std::unique_ptr<Registry>& registry) {
        bool clean;
        for (long unsigned int i = 0; i < registry->enemiesToSpawn.size(); i++) {
            clean = false;
            for (auto& entity : GetSystemEntities()) {
                if(entity.GetComponent<EnemyComponent>().group ==
                   registry->enemiesToSpawn[i].groupNumber) {
                    clean = true;
                    break;
                }
            }
            if (!clean) {
                std::cout << "[CLEANENEMIESSYSTEM] Se elimina el grupo " <<
                    registry->enemiesToSpawn[i].groupNumber << std::endl;
                registry->enemiesToSpawn.erase(registry->enemiesToSpawn.begin() + i);
            }
        }
    }

    /**
     * @brief Removes enemy entities that have moved outside the screen boundaries
     * 
     * Checks all enemy entities to determine if they have moved completely
     * outside the visible screen area. Entities that are no longer visible
     * are marked for destruction to free up resources.
     * 
     * An entity is considered hidden if:
     * - Its right edge is to the left of the screen (x + width < 0)
     * - Its bottom edge is above the screen (y + height < 0)  
     * - Its top edge is below the screen (y + height > screen_height)
     */
    void CleanHiddenEnemies() {
        for (auto entity : GetSystemEntities()) {
            Entity& a = entity;
            auto sprite = a.GetComponent<SpriteComponent>();
            auto transform = a.GetComponent<TransformComponent>();
            
            if ((transform.position.x + (sprite.width * transform.scale.x)) < 0 ||
                (transform.position.y + (sprite.height * transform.scale.y)) < 0 ||
                (transform.position.y + (sprite.height * transform.scale.y)) > height) {
                std::cout << "[CLEANENEMIESSYSTEM] Se elimina la entidad " << a.GetId()
                    << " debido a que sale de pantalla\n";
                a.Kill();
            }
        }
    }

public:
    /**
     * @brief Constructs the clean enemies system and sets component requirements
     * 
     * Initializes the system to require EnemyComponent, TransformComponent,
     * and SpriteComponent for entities to be processed by this system.
     */
    CleanEnemiesSystem() {
        RequireComponent<EnemyComponent>();
        RequireComponent<TransformComponent>();
        RequireComponent<SpriteComponent>();
    }

    /**
     * @brief Sets the screen dimensions for boundary checking
     * @param height Screen height in pixels
     * @param width Screen width in pixels
     * 
     * Configures the screen boundaries used to determine when enemies
     * have moved outside the visible area and should be cleaned up.
     */
    void SetParameter(int height, int width) {
        this->height = height;
        this->width = width;
    }

    /**
     * @brief Updates the system by cleaning hidden enemies and empty groups
     * @param registry Reference to the game registry for spawn group management
     * 
     * Performs two main cleanup operations:
     * 1. Removes enemies that have moved outside screen boundaries
     * 2. Cleans up empty enemy spawn groups from the registry
     * 
     * This method should be called regularly during the game loop to
     * maintain optimal performance and memory usage.
     */
    void Update(std::unique_ptr<Registry>& registry) {
        CleanHiddenEnemies();
        CleanEnemyGroups(registry);
    }
};

#endif // CLEANENEMIESSYSTEM_HPP