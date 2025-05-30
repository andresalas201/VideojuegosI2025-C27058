/**
 * @file SceneLoader.hpp
 * @brief Defines the SceneLoader class for loading and configuring game scenes from Lua scripts
 */

#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP
#include <SDL2/SDL.h>
#include <memory>
#include <sol/sol.hpp>
#include <string>
#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class SceneLoader
 * @brief Handles loading and initialization of game scenes from Lua configuration files
 * 
 * The SceneLoader class is responsible for parsing Lua scene configuration files
 * and setting up all necessary game components including assets, entities, controls,
 * audio, and scene transitions. It provides a unified interface for loading
 * complete game scenes with all their dependencies.
 */
class SceneLoader {
private:
    /**
     * @brief Loads scene transition configuration
     * 
     * Parses the next scenes table from Lua configuration and sets up
     * scene transition logic in the registry.
     * 
     * @param registry ECS registry to configure scene transitions
     * @param nextScenes Lua table containing scene transition data
     */
    void LoadNextScenes(std::unique_ptr<Registry>& registry,
                        const sol::table& nextScenes);
    
    /**
     * @brief Loads sprite textures and assets
     * 
     * Parses sprite configuration from Lua and loads all texture assets
     * into the asset manager for use in the scene.
     * 
     * @param renderer SDL renderer for texture loading
     * @param sprites Lua table containing sprite asset definitions
     * @param assetManager Asset manager to store loaded textures
     */
    void LoadSprites(SDL_Renderer* renderer,
                     const sol::table& sprites,
                     std::unique_ptr<AssetManager>& assetManager);
    
    /**
     * @brief Loads font assets for text rendering
     * 
     * Parses font configuration from Lua and loads all font assets
     * into the asset manager.
     * 
     * @param fonts Lua table containing font asset definitions
     * @param assetManager Asset manager to store loaded fonts
     */
    void LoadFonts(const sol::table& fonts,
                   std::unique_ptr<AssetManager>& assetManager);
    
    /**
     * @brief Loads keyboard input bindings
     * 
     * Parses keyboard configuration from Lua and sets up key bindings
     * in the controller manager.
     * 
     * @param keys Lua table containing keyboard binding definitions
     * @param controllerManager Controller manager to configure key bindings
     */
    void LoadKeys(const sol::table& keys,
                  std::unique_ptr<ControllerManager>& controllerManager);
    
    /**
     * @brief Loads gamepad button bindings
     * 
     * Parses gamepad button configuration from Lua and sets up button
     * bindings in the controller manager.
     * 
     * @param buttons Lua table containing button binding definitions
     * @param controllerManager Controller manager to configure button bindings
     */
    void LoadButtons(const sol::table& buttons,
                     std::unique_ptr<ControllerManager>& controllerManager);
    
    /**
     * @brief Loads and creates scene entities
     * 
     * Parses entity configuration from Lua and creates all entities
     * with their components in the ECS registry.
     * 
     * @param lua Lua state for script execution
     * @param entities Lua table containing entity definitions
     * @param registry ECS registry to create entities in
     */
    void LoadEntities(sol::state& lua, const sol::table& entities,
                      std::unique_ptr<Registry>& registry);
    
    /**
     * @brief Starts background music for the scene
     * 
     * Parses music configuration from Lua and creates music entities
     * or triggers background music playback.
     * 
     * @param music Lua table containing music configuration
     * @param registry ECS registry for music entity creation
     */
    void StartMusic(const sol::table& music, std::unique_ptr<Registry>& registry);
    
    /**
     * @brief Loads sound effect assets
     * 
     * Parses sound configuration from Lua and loads all audio assets
     * into the asset manager for use in the scene.
     * 
     * @param sounds Lua table containing sound asset definitions
     * @param assetManager Asset manager to store loaded audio assets
     */
    void LoadSound(const sol::table& sounds, std::unique_ptr<AssetManager>& assetManager);
    
    /**
     * @brief Loads enemy entities and AI behavior
     * 
     * Parses enemy configuration from Lua and creates enemy entities
     * with their AI scripts and behaviors in the ECS registry.
     * 
     * @param lua Lua state for AI script execution
     * @param enemies Lua table containing enemy definitions
     * @param registry ECS registry to create enemy entities in
     */
    void LoadEnemies(sol::state& lua, const sol::table& enemies, std::unique_ptr<Registry>& registry);

public:
    /**
     * @brief Constructs a new SceneLoader
     * 
     * Initializes the scene loader with default settings.
     */
    SceneLoader();
    
    /**
     * @brief Destructs the SceneLoader
     * 
     * Cleans up any resources used by the scene loader.
     */
    ~SceneLoader();
    
    /**
     * @brief Loads a complete game scene from a Lua configuration file
     * 
     * This is the main entry point for scene loading. It parses the specified
     * Lua scene file and loads all components including assets, entities,
     * controls, audio, and scene configuration into the provided managers
     * and registry.
     * 
     * @param scenePath File path to the Lua scene configuration file
     * @param lua Lua state for script execution and configuration parsing
     * @param assetManager Asset manager to load textures, fonts, and sounds
     * @param controllerManager Controller manager to configure input bindings
     * @param registry ECS registry to create entities and components
     * @param renderer SDL renderer for texture loading operations
     */
    void LoadScene(const std::string& scenePath, sol::state& lua,
                   std::unique_ptr<AssetManager>& assetManager,
                   std::unique_ptr<ControllerManager>& controllerManager,
                   std::unique_ptr<Registry>& registry,
                   SDL_Renderer* renderer);
};
#endif // SCENELOADER_HPP