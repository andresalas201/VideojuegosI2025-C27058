/**
 * @file PlayerComponent.hpp
 * @brief Component for identifying and managing player entities in the game system
 */

#ifndef PLAYERCOMPONENT_HPP
#define PLAYERCOMPONENT_HPP

/**
 * @struct PlayerComponent
 * @brief A component that identifies an entity as a player and tracks player number
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to mark entities as player-controlled characters and distinguish between
 * multiple players in multiplayer scenarios. It enables systems to identify
 * which entities should respond to player input and apply player-specific
 * logic, scoring, or UI elements.
 */
struct PlayerComponent {
    /**
     * @brief Unique identifier for the player
     * 
     * Integer value that distinguishes between different players in
     * multiplayer games. Typically starts from 1 for player 1, 2 for
     * player 2, etc. A value of 0 may indicate an unassigned or
     * default player state.
     */
    int playerNumber;
    
    /**
     * @brief Constructor for PlayerComponent
     * 
     * Initializes the player component with a specific player number
     * for identification and multiplayer management.
     * 
     * @param playerNumber The unique identifier for this player (default: 0)
     */
    PlayerComponent(int playerNumber = 0) {
        this->playerNumber = playerNumber;
    }
};

#endif // PLAYERCOMPONENT_HPP