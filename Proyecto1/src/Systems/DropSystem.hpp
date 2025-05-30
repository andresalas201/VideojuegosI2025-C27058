/**
 * @file DropSystem.hpp
 * @brief Defines the DropSystem class for handling item drops when entity groups are defeated
 */

#ifndef DROPSYSTEM_HPP
#define DROPSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/GroupDeathEvent.hpp"
#include "../Components/DropComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/UpgradeComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"

/**
 * @class DropSystem
 * @brief System responsible for creating item drops when entity groups are eliminated
 * 
 * The DropSystem listens for GroupDeathEvent notifications and creates upgrade items
 * at the location where enemy groups were defeated. These dropped items can be collected
 * by players to gain various upgrades and enhancements. The system handles the complete
 * creation of drop entities with all necessary components for interaction.
 */
class DropSystem : public System {
public:
    /**
     * @brief Constructor that sets up required components for the drop system
     * 
     * Requires entities to have DropComponent to be processed by this system.
     * Only entities with drop capabilities will be monitored for group death events.
     */
    DropSystem() {
        RequireComponent<DropComponent>();
    }

    /**
     * @brief Subscribes the drop system to group death events
     * @param eventManager Unique pointer to the event manager
     * 
     * Registers the OnGroupDeath method to be called whenever a GroupDeathEvent occurs,
     * allowing the system to create item drops when enemy groups are completely eliminated.
     */
    void SubscribeToGroupDeathEvent(std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<GroupDeathEvent, DropSystem>(this,
            &DropSystem::OnGroupDeath);
    }

    /**
     * @brief Handles group death events and creates item drops
     * @param e Reference to the GroupDeathEvent containing the last entity of the defeated group
     * 
     * When an enemy group is completely eliminated, this method creates a new drop entity
     * at the location of the last defeated enemy. The drop entity is configured with:
     * - Visual representation (sprite) based on the drop component configuration
     * - Upgrade functionality that can be applied to collecting entities
     * - Transform component positioned at the death location
     * - Collision detection for player interaction
     * - Health component for drop lifetime management
     * 
     * The created drop entity is automatically registered with all relevant systems.
     */
    void OnGroupDeath(GroupDeathEvent& e) {
        if (e.a.HasComponent<DropComponent>()) {
            auto dropBase = e.a.GetComponent<DropComponent>();
            auto transform = e.a.GetComponent<TransformComponent>();
            
            std::cout << "[DROPSYSTEM] La entidad " << e.a.GetId() << " hace un drop\n";
            
            // Create new drop entity
            Entity drop = e.a.registry->CreateEntity();
            
            // Add visual representation
            drop.AddComponent<SpriteComponent>(dropBase.textureId, dropBase.width,
                dropBase.height, dropBase.srcRect.x, dropBase.srcRect.y);
            
            // Add upgrade functionality
            drop.AddComponent<UpgradeComponent>(dropBase.upgrade, dropBase.increase);
            
            // Position at death location
            drop.AddComponent<TransformComponent>(transform.position);
            
            // Add collision detection for pickup
            drop.AddComponent<CircleColliderComponent>(dropBase.radius, dropBase.width,
                dropBase.height);
            
            // Add health for drop management (1 health, 0 damage resistance)
            drop.AddComponent<HealthComponent>(1, 0);
            
            // Register drop entity with all systems
            e.a.registry->AddEntityToSystems(drop);
        }
    }
};

#endif // DROPSYSTEM_HPP