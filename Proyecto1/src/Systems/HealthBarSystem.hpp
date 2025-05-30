/**
 * @file HealthBarSystem.hpp
 * @brief Health bar system implementation for ECS architecture
 */

#ifndef HEALTHBARSYSTEM_HPP
#define HEALTHBARSYSTEM_HPP
#include "../ECS/ECS.hpp"
#include "../Components/HealthBarComponent.hpp"
#include "../Components/TextComponent.hpp"

/**
 * @class HealthBarSystem
 * @brief System responsible for managing and updating health bar displays
 * 
 * This system handles the visual representation of player health status by updating
 * text components to display current health values or death status. It requires
 * entities to have both HealthBarComponent and TextComponent.
 */
class HealthBarSystem : public System {
public:
    /**
     * @brief Constructor for HealthBarSystem
     * 
     * Sets up the system to require HealthBarComponent and TextComponent
     * for all entities it will process.
     */
    HealthBarSystem() {
        RequireComponent<HealthBarComponent>();
        RequireComponent<TextComponent>();
    }

    /**
     * @brief Updates all health bar text displays
     * 
     * Iterates through all entities with health bars and updates their
     * text components to show either current health or death status.
     * Players are numbered sequentially starting from 1.
     */
    void Update() {
        int index = 1;
        for (auto entity : GetSystemEntities()) {
            auto& text = entity.GetComponent<TextComponent>();
            auto healthBar = entity.GetComponent<HealthBarComponent>();
            if (healthBar.health <= 0) text.text = "P" + std::to_string(index) +" Is Dead";
            else text.text = "P" + std::to_string(index) +" Health: " + std::to_string(healthBar.health);
            index++;
        }
    }

    /**
     * @brief Sets the health value for a specific player
     * 
     * @param health The new health value to set
     * @param player The player index (0-based) to update
     * 
     * Updates the health component of the specified player entity.
     * If the player index is out of bounds, no action is taken.
     */
    void SetHealth(int health, int player) {
        std::vector<Entity> entities = GetSystemEntities();
        if(player < static_cast<int>(entities.size())) {
            auto& healthBar = entities[player].GetComponent<HealthBarComponent>();
            healthBar.health = health;
        }
    }
};
#endif // HEALTHBARSYSTEM_HPP