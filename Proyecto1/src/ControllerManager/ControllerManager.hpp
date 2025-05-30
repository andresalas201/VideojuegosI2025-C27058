#ifndef CONTROLLERMANAGER_HPP
#define CONTROLLERMANAGER_HPP
#include <SDL2/SDL.h>
#include <map>
#include <string>

/**
 * @brief Manages input handling for keyboard and mouse interactions.
 * 
 * ControllerManager provides a centralized system for managing input events
 * from keyboard and mouse devices. It allows mapping of key codes and mouse
 * buttons to named actions, tracking input states, and querying current
 * input status. This class abstracts SDL input handling and provides a
 * more convenient interface for game input management.
 */
class ControllerManager {
private:
    /** @brief Maps action names to their corresponding key codes */
    std::map<std::string, int> actionKeyName;
    
    /** @brief Tracks the current pressed state of each key code */
    std::map<int, bool> keyDown;
    
    /** @brief Maps mouse button names to their corresponding button codes */
    std::map<std::string, int> mouseButtonName;
    
    /** @brief Tracks the current pressed state of each mouse button code */
    std::map<int, bool> mouseButtonDown;
    
    /** @brief Current X coordinate of the mouse cursor */
    int mousePosX;
    
    /** @brief Current Y coordinate of the mouse cursor */
    int mousePosY;

public:
    /**
     * @brief Constructs a ControllerManager and initializes input tracking.
     * 
     * Initializes all internal data structures and sets up the input
     * management system for keyboard and mouse input handling.
     */
    ControllerManager();
    
    /**
     * @brief Destructor for ControllerManager.
     * 
     * Cleans up any resources used by the input management system.
     */
    ~ControllerManager();
    
    /**
     * @brief Clears all input mappings and resets input states.
     * 
     * Removes all registered action mappings, mouse button mappings,
     * and resets all input states to their default values.
     */
    void Clear();

    // Keyboard
    /**
     * @brief Associates a named action with a specific key code.
     * 
     * Creates a mapping between a string-based action name and an SDL
     * key code, allowing for more readable and maintainable input handling.
     * 
     * @param action String identifier for the action (e.g., "jump", "fire")
     * @param keyCode SDL key code to associate with the action
     */
    void AddActionKey(const std::string& action, int keyCode);
    
    /**
     * @brief Registers that a key has been pressed down.
     * 
     * Updates the internal key state to reflect that the specified
     * key is currently being held down.
     * 
     * @param keyCode SDL key code of the pressed key
     */
    void KeyDown(int keyCode);
    
    /**
     * @brief Registers that a key has been released.
     * 
     * Updates the internal key state to reflect that the specified
     * key is no longer being held down.
     * 
     * @param keyCode SDL key code of the released key
     */
    void KeyUp(int keyCode);
    
    /**
     * @brief Checks if a named action is currently activated.
     * 
     * Determines whether the key associated with the given action
     * name is currently being pressed.
     * 
     * @param action String identifier for the action to check
     * @return true if the action's associated key is pressed, false otherwise
     */
    bool IsActionActivated(const std::string& action);

    // Mouse
    /**
     * @brief Associates a named mouse button with a specific button code.
     * 
     * Creates a mapping between a string-based button name and an SDL
     * mouse button code for easier mouse input management.
     * 
     * @param name String identifier for the mouse button (e.g., "left", "right")
     * @param buttonCode SDL mouse button code to associate with the name
     */
    void AddMouseButton(const std::string& name, int buttonCode);
    
    /**
     * @brief Registers that a mouse button has been pressed down.
     * 
     * Updates the internal mouse button state to reflect that the
     * specified button is currently being held down.
     * 
     * @param buttonCode SDL mouse button code of the pressed button
     */
    void MouseButtonDown(int buttonCode);
    
    /**
     * @brief Registers that a mouse button has been released.
     * 
     * Updates the internal mouse button state to reflect that the
     * specified button is no longer being held down.
     * 
     * @param buttonCode SDL mouse button code of the released button
     */
    void MouseButtonUp(int buttonCode);
    
    /**
     * @brief Checks if a named mouse button is currently pressed.
     * 
     * Determines whether the mouse button associated with the given
     * name is currently being held down.
     * 
     * @param name String identifier for the mouse button to check
     * @return true if the named mouse button is pressed, false otherwise
     */
    bool IsMouseButtonDown(const std::string& name);
    
    /**
     * @brief Updates the current mouse cursor position.
     * 
     * Sets the internal tracking of the mouse cursor coordinates
     * to the specified screen position.
     * 
     * @param x X coordinate of the mouse cursor
     * @param y Y coordinate of the mouse cursor
     */
    void SetMousePosition(int x, int y);
    
    /**
     * @brief Retrieves the current mouse cursor position.
     * 
     * Returns the current X and Y coordinates of the mouse cursor
     * as tracked by the input manager.
     * 
     * @return std::tuple<int, int> containing (x, y) coordinates of the mouse cursor
     */
    std::tuple<int, int> GetMousePosition();
};

#endif // CONTROLLERMANAGER_HPP