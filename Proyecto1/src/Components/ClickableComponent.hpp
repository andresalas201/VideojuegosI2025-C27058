/**
 * @file ClickableComponent.hpp
 * @brief Component for handling clickable interactions in the game system
 */

#ifndef CLICKABLECOMPONENT_HPP
#define CLICKABLECOMPONENT_HPP

/**
 * @struct ClickableComponent
 * @brief A component that enables entities to respond to click events
 * 
 * This component is used in an Entity-Component-System (ECS) architecture
 * to make entities interactive through mouse clicks or touch events.
 * When attached to an entity, it allows the entity to detect and respond
 * to user click interactions.
 */
struct ClickableComponent {
    /**
     * @brief Flag indicating whether the entity has been clicked
     * 
     * This boolean flag tracks the current click state of the entity.
     * It is set to true when the entity is clicked and can be used
     * by systems to trigger click-based behaviors or responses.
     */
    bool isClicked;
    
    /**
     * @brief Default constructor for ClickableComponent
     * 
     * Initializes the component with isClicked set to false, indicating
     * that the entity starts in an unclicked state.
     */
    ClickableComponent () {
        isClicked = false;
    }
};

#endif // CLICKABLECOMPONENT_HPP