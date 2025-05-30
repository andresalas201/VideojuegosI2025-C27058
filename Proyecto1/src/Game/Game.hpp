/**
 * @file Game.hpp
 * @brief Defines the Game class which serves as the main game engine and singleton controller
 */

#ifndef GAME_HPP
#define GAME_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include "../AssetManager/AssetManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../ECS/ECS.hpp"
#include "../SceneManager/SceneManager.hpp"

/**
 * @brief Global variable defining the target frames per second
 */
extern int FPS;

/**
 * @brief Global variable defining milliseconds per frame for timing calculations
 */
extern int MILLISECS_PER_FRAME;

/**
 * @class Game
 * @brief Main game engine class implementing the singleton pattern
 * 
 * This class serves as the central controller for the entire game engine.
 * It manages the game loop, SDL initialization, rendering, input processing,
 * and coordinates all major game systems including ECS, asset management,
 * event handling, and scene management.
 */
class Game {
private:
    /**
     * @brief SDL window handle
     */
    SDL_Window* window = nullptr;
    
    /**
     * @brief Time interval between shots in seconds
     */
    int secondsPerShot = 0;
    
    /**
     * @brief Wait time for entity spawning
     */
    int spawnWait = 0;
    
    /**
     * @brief Current boss score tracking
     */
    int bossScore = 0;
    
    /**
     * @brief Timestamp of the previous frame in milliseconds
     * 
     * Used for delta time calculations and frame rate control
     */
    int milisecsPreviousFrame = 0;
    
    /**
     * @brief Flag indicating if the game is currently running
     */
    bool isRunning = false;
    
    /**
     * @brief Flag indicating if the game is currently paused
     */
    bool isPaused = false;
    
    /**
     * @brief Initializes game systems and components
     * 
     * Private method called during game initialization to set up
     * all necessary game systems and load initial resources.
     */
    void Setup();
    
    /**
     * @brief Executes the current scene logic
     * 
     * Private method that handles scene-specific game logic and updates.
     */
    void RunScene();
    
    /**
     * @brief Processes user input events
     * 
     * Private method that handles keyboard, mouse, and controller input
     * during each frame of the game loop.
     */
    void ProcessInput();
    
    /**
     * @brief Updates game state and logic
     * 
     * Private method called each frame to update entity components,
     * physics, AI, and other game systems.
     */
    void Update();
    
    /**
     * @brief Renders the current frame
     * 
     * Private method that handles all rendering operations including
     * sprites, UI, and visual effects.
     */
    void Render();
    
    /**
     * @brief Loads game configuration settings
     * 
     * Private method that reads and applies configuration files
     * for game settings and parameters.
     */
    void LoadConfig();
    
    /**
     * @brief Private constructor for singleton pattern
     * 
     * Prevents direct instantiation of the Game class.
     */
    Game();
    
    /**
     * @brief Private destructor for singleton pattern
     * 
     * Handles cleanup when the Game instance is destroyed.
     */
    ~Game();

public:
    /**
     * @brief Width of the game window in pixels
     */
    int windowWidth = 0;
    
    /**
     * @brief Height of the game window in pixels
     */
    int windowHeight = 0;
    
    /**
     * @brief Asset management system
     * 
     * Handles loading, storing, and retrieving of game assets
     * such as textures, sounds, and fonts.
     */
    std::unique_ptr<AssetManager> assetManager;
    
    /**
     * @brief Event management system
     * 
     * Handles game event dispatching and subscription management.
     */
    std::unique_ptr<EventManager> eventManager;
    
    /**
     * @brief Entity Component System registry
     * 
     * Core ECS registry that manages all entities and their components.
     */
    std::unique_ptr<Registry> registry;
    
    /**
     * @brief Scene management system
     * 
     * Handles loading, switching, and managing different game scenes.
     */
    std::unique_ptr<SceneManager> sceneManager;
    
    /**
     * @brief Lua scripting state
     * 
     * Sol2 Lua state for handling game scripting and configuration.
     */
    sol::state lua;
    
    /**
     * @brief SDL renderer handle
     * 
     * Main SDL renderer used for all graphics rendering operations.
     */
    SDL_Renderer* renderer = nullptr;
    
    /**
     * @brief SDL audio device handle
     * 
     * Audio device used for sound playback and audio management.
     */
    SDL_AudioDeviceID* audioDevice = nullptr;
    
    /**
     * @brief Input controller management system
     * 
     * Handles gamepad and controller input processing.
     */
    std::unique_ptr<ControllerManager> controllerManager;
    
    /**
     * @brief Gets the singleton instance of the Game class
     * 
     * @return Reference to the single Game instance
     */
    static Game& GetInstance();
    
    /**
     * @brief Initializes the game engine
     * 
     * Sets up SDL, creates the window, initializes all game systems,
     * and prepares the game for execution.
     */
    void Init();
    
    /**
     * @brief Runs the main game loop
     * 
     * Executes the core game loop handling input, updates, and rendering
     * until the game is terminated.
     */
    void Run();
    
    /**
     * @brief Cleans up and destroys game resources
     * 
     * Properly shuts down all game systems, releases resources,
     * and performs cleanup operations.
     */
    void Destroy();
};
#endif // GAME_HPH