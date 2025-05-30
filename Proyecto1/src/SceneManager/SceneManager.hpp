/**
 * @file SceneManager.hpp
 * @brief Defines the SceneManager class for managing game scene lifecycle and transitions
 */

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#include <map>
#include <memory>
#include <sol/sol.hpp>
#include <string>
#include "SceneLoader.hpp"

/**
 * @class SceneManager
 * @brief Manages game scene lifecycle, transitions, and state
 * 
 * The SceneManager class handles the loading, switching, and management of
 * game scenes. It maintains a registry of available scenes, tracks the current
 * scene state, and coordinates scene transitions. It works closely with the
 * SceneLoader to handle the actual loading of scene assets and configuration.
 */
class SceneManager {
private:
    /**
     * @brief Map of scene names to their file paths
     * 
     * Stores the mapping between scene identifiers and their corresponding
     * Lua configuration file paths for scene loading.
     */
    std::map<std::string, std::string> scenes;
    
    /**
     * @brief Identifier of the next scene to be loaded
     * 
     * Holds the name of the scene that should be loaded during the
     * next scene transition.
     */
    std::string nextScene;
    
    /**
     * @brief Flag indicating if a scene is currently running
     * 
     * Tracks whether a scene is actively running to manage scene
     * state and prevent invalid operations.
     */
    bool isSceneRunning = false;
    
    /**
     * @brief Scene loader instance for handling scene loading operations
     * 
     * Manages the actual loading of scene assets, entities, and configuration
     * from Lua files.
     */
    std::unique_ptr<SceneLoader> sceneLoader;

public:
    /**
     * @brief Constructs a new SceneManager
     * 
     * Initializes the scene manager with default settings and creates
     * the scene loader instance.
     */
    SceneManager();
    
    /**
     * @brief Destructs the SceneManager
     * 
     * Cleans up scene manager resources and stops any running scenes.
     */
    ~SceneManager();
    
    /**
     * @brief Loads scene configuration from a Lua script file
     * 
     * Parses a Lua script to extract scene definitions and register them
     * in the scene manager. This method reads scene metadata and file paths
     * but does not immediately load the scene assets.
     * 
     * @param path File path to the Lua script containing scene definitions
     * @param lua Lua state for script parsing and execution
     */
    void LoadSceneFromScript(const std::string& path, sol::state& lua);
    
    /**
     * @brief Loads the currently selected scene
     * 
     * Triggers the loading of the scene specified by the current nextScene
     * identifier. This method coordinates with the SceneLoader to load all
     * scene assets, entities, and configuration.
     */
    void LoadScene();
    
    /**
     * @brief Gets the identifier of the next scene to be loaded
     * 
     * @return The scene identifier string for the next scene
     */
    std::string GetNextScene() const;
    
    /**
     * @brief Sets the next scene to be loaded during transition
     * 
     * Specifies which scene should be loaded during the next scene
     * transition operation.
     * 
     * @param nextScene Identifier of the scene to load next
     */
    void SetNextScene(const std::string& nextScene);
    
    /**
     * @brief Checks if a scene is currently running
     * 
     * @return True if a scene is actively running, false otherwise
     */
    bool IsSceneRunning() const;
    
    /**
     * @brief Starts the current scene execution
     * 
     * Marks the current scene as running and enables scene-specific
     * game logic and updates.
     */
    void StartScene();
    
    /**
     * @brief Stops the current scene execution
     * 
     * Marks the current scene as stopped and disables scene-specific
     * game logic, preparing for scene transition or game shutdown.
     */
    void StopScene();
};
#endif // SCENEMANAGER_HPP