/**
 * @file UISystem.hpp
 * @brief Header file for the UISystem class
 */

#ifndef UISYSTEM_HPP
#define UISYSTEM_HPP
#include <SDL2/SDL.h>
#include <sol/sol.hpp>
#include <memory>
#include <iostream>
#include <string>
#include "../ECS/ECS.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/ClickEvent.hpp"

/**
 * @class UISystem
 * @brief System responsible for handling user interface interactions
 * 
 * This system manages clickable UI elements by detecting click events within
 * the bounds of text-based UI components and executing associated Lua scripts.
 * It requires entities to have ClickableComponent, TextComponent, and TransformComponent.
 */
class UISystem : public System {
public:
    /**
     * @brief Constructor for UISystem
     * 
     * Sets up the system to require ClickableComponent, TextComponent, and
     * TransformComponent for entities to be processed by this system.
     */
    UISystem() {
        RequireComponent<ClickableComponent>();
        RequireComponent<TextComponent>();
        RequireComponent<TransformComponent>();
    }
    
    /**
     * @brief Subscribes to click events from the event manager
     * 
     * Registers this system to receive ClickEvent notifications, enabling
     * it to respond to user click interactions.
     * 
     * @param eventManager Reference to the event manager for event subscription
     */
    void SubscribeToClicEvent (std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<ClickEvent, UISystem>(this,
            &UISystem::OnClickEvent);
    }
    
    /**
     * @brief Event handler for click events
     * 
     * Processes click events by checking if the click position falls within
     * the bounds of any clickable UI elements. If a click is detected within
     * an element's bounds and the element has a ScriptComponent with an onClick
     * function, the function is executed.
     * 
     * @param e Reference to the ClickEvent containing click position data
     */
    void OnClickEvent(ClickEvent& e) {
        for (auto entity : GetSystemEntities()) {
            const auto& text = entity.GetComponent<TextComponent>();
            const auto& transform = entity.GetComponent<TransformComponent>();
            if(transform.position.x < e.posX &&
               e.posX < transform.position.x + text.width &&
               transform.position.y < e.posY &&
               e.posY < transform.position.y + text.height) {
                if (entity.HasComponent<ScriptComponent>()) {
                    const auto& script = entity.GetComponent<ScriptComponent>();
                    if (script.onClick != sol::nil) {
                        script.onClick();
                    }
                }
            }
        }
    }
};
#endif // UISYSTEM_HPP