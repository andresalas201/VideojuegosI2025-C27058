/**
 * @file HealthBarComponent.hpp
 * @brief Component for displaying health bar UI elements in the game system
 */

#ifndef HEALTHBARCOMPONENT_HPP
#define HEALTHBARCOMPONENT_HPP

/**
 * @struct HealthBarComponent
 * @brief A component that manages health bar display and tracking
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to create and manage health bar UI elements. It tracks the current health
 * value and determines which player the health bar belongs to, enabling
 * proper positioning and styling of health bars in multiplayer scenarios.
 */
struct HealthBarComponent {
    /**
     * @brief Flag indicating whether this health bar belongs to player 1
     * 
     * Boolean flag used to determine which player this health bar represents.
     * When true, the health bar belongs to player 1; when false, it may
     * belong to player 2 or another entity. This affects positioning,
     * color scheme, and display logic for the health bar.
     */
    bool isPlayer1;
    
    /**
     * @brief Current health value to display on the health bar
     * 
     * Integer representing the current health points that should be
     * displayed by this health bar. This value is used to calculate
     * the visual representation of the health bar's fill level.
     */
    int health;
    
    /**
     * @brief Constructor for HealthBarComponent
     * 
     * Initializes the health bar component with player identification
     * and initial health value for proper display and tracking.
     * 
     * @param isPlayer1 Flag indicating if this belongs to player 1 (default: true)
     * @param health Initial health value to display (default: 0)
     */
    HealthBarComponent(bool isPlayer1 = true ,int health = 0) {
        this->isPlayer1 = isPlayer1;
        this->health = health;
    }
};

#endif // HEALTHBARCOMPONENT_HPP