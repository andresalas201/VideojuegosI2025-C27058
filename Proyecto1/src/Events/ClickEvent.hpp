/**
 * @file ClickEvent.hpp
 * @brief Defines the ClickEvent class for handling mouse click events
 */

#ifndef CLICKEVENT_HPP
#define CLICKEVENT_HPP
#include "../ECS/ECS.hpp"
#include "../EventManager/Event.hpp"

/**
 * @class ClickEvent
 * @brief Event class that represents a mouse click action
 * 
 * This class inherits from the Event base class and is used to notify
 * systems when a mouse click occurs. It captures the button that was
 * clicked and the position coordinates of the click.
 */
class ClickEvent : public Event {
public:
    /**
     * @brief The mouse button code that was clicked
     * 
     * Represents which mouse button triggered the click event
     * (e.g., left button, right button, middle button)
     */
    int buttonCode;
    
    /**
     * @brief The X coordinate of the click position
     * 
     * Horizontal position where the mouse click occurred
     */
    int posX;
    
    /**
     * @brief The Y coordinate of the click position
     * 
     * Vertical position where the mouse click occurred
     */
    int posY;
    
    /**
     * @brief Constructs a new ClickEvent
     * 
     * @param buttonCode The mouse button code (default: 0)
     * @param posX The X coordinate of the click (default: 0)
     * @param posY The Y coordinate of the click (default: 0)
     */
    ClickEvent(int buttonCode = 0, int posX = 0, int posY = 0) {
        this->buttonCode = buttonCode;
        this->posX = posX;
        this->posY = posY;
    }
};
#endif // CLICKEVENT_HPP