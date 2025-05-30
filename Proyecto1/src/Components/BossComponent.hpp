/**
 * @file BossComponent.hpp
 * @brief Component for marking entities as boss entities in the game system
 */

#ifndef BOSSCOMPONENT_HPP
#define BOSSCOMPONENT_HPP

/**
 * @struct BossComponent
 * @brief A component that identifies an entity as a boss entity
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to mark entities that should be treated as boss entities. When attached
 * to an entity, it indicates that the entity has boss-level properties
 * and should be handled accordingly by relevant systems.
 */
struct BossComponent {
    /**
     * @brief Flag indicating whether the entity is a boss
     * 
     * This boolean flag is automatically set to true when the component
     * is constructed, marking the entity as a boss entity.
     */
    bool isBoss;
    
    /**
     * @brief Default constructor for BossComponent
     * 
     * Initializes the component with isBoss set to true, automatically
     * marking any entity with this component as a boss entity.
     */
    BossComponent() { 
        this->isBoss = true; 
    };
};

#endif // BOSSCOMPONENT_HPP