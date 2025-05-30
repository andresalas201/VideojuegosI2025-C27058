/**
 * @file PreEntity.hpp
 * @brief Defines the PreEntity class used for dynamic entity creation and spawning
 */

#ifndef PREENTITY_HPP
#define PREENTITY_HPP
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <SDL2/SDL.h>

class Registry;

/**
 * @class PreEntity
 * @brief Template class for dynamic entity creation and spawning
 * 
 * PreEntity serves as a blueprint for creating entities dynamically during runtime.
 * It allows configuration of all entity components and properties before spawning
 * the actual entity into the ECS registry. This class supports complex entity
 * setups including animations, attacks, colliders, health, sprites, and more.
 */
class PreEntity {
private:
    /**
     * @brief Number of animation frames
     */
    int numFrames;
    
    /**
     * @brief Current animation frame index
     */
    int currentFrame;
    
    /**
     * @brief Animation frame speed rate
     */
    int frameSpeedRate;
    
    /**
     * @brief Whether animation should loop
     */
    bool isLoop;
    
    /**
     * @brief Start time for animation timing
     */
    int startTime;
    
    /**
     * @brief Damage dealt by attacks
     */
    int attackDamage;
    
    /**
     * @brief Radius of attack area
     */
    int attackRadius;
    
    /**
     * @brief Width of attack area
     */
    int attackWidth;
    
    /**
     * @brief Height of attack area
     */
    int attackHeight;
    
    /**
     * @brief Texture ID for attack visuals
     */
    std::string attackTextureId;
    
    /**
     * @brief Collision radius for circular colliders
     */
    int radius;
    
    /**
     * @brief Width for rectangular colliders
     */
    int width;
    
    /**
     * @brief Height for rectangular colliders
     */
    int height;
    
    /**
     * @brief Source rectangle for attack sprite
     */
    SDL_Rect attackSrcRect;
    
    /**
     * @brief Velocity vector for attack projectiles
     */
    glm::vec2 attackVelocity;
    
    /**
     * @brief Movement velocity of the entity
     */
    glm::vec2 velocity;
    
    /**
     * @brief File path for shooting sound effect
     */
    std::string shootSoundFilePath;
    
    /**
     * @brief File path for hit sound effect
     */
    std::string hitSoundFilePath;
    
    /**
     * @brief Scale factor for attack visuals
     */
    glm::vec2 attackScale;
    
    /**
     * @brief Maximum number of shots allowed
     */
    int maxShots;
    
    /**
     * @brief Current number of shots fired
     */
    int currentShots;
    
    /**
     * @brief Direction flag for left-facing attacks
     */
    bool left;
    
    /**
     * @brief Number of frames in attack animation
     */
    int attackNumFrames;
    
    /**
     * @brief Frame speed rate for attack animation
     */
    int attackFrameSpeedRate;
    
    /**
     * @brief Whether attack animation should loop
     */
    bool isAttackLoop;
    
    /**
     * @brief Lua function for attack update logic
     */
    sol::function attackUpdate;
    
    /**
     * @brief Scale factor for entity sprite
     */
    glm::vec2 scale;
    
    /**
     * @brief Timestamp of last shot fired
     */
    int lastShotTick;
    
    /**
     * @brief Number of projectiles per shot
     */
    int shotQuantity;
    
    /**
     * @brief Death state flag
     */
    bool isDead;
    
    /**
     * @brief Entity health points
     */
    int health;
    
    /**
     * @brief Name identifier for sound effects
     */
    std::string soundName;
    
    /**
     * @brief Damage dealt to other entities
     */
    int damage;
    
    /**
     * @brief Source rectangle for main sprite
     */
    SDL_Rect srcRect;
    
    /**
     * @brief Texture ID for main sprite
     */
    std::string textureId;
    
    /**
     * @brief Source rectangle for hit animation sprite
     */
    SDL_Rect hitSrcRect;
    
    /**
     * @brief X coordinate for upward movement sprite
     */
    int upX;
    
    /**
     * @brief X coordinate for downward movement sprite
     */
    int downX;
    
    /**
     * @brief X coordinate for hit animation when moving up
     */
    int hitUpX;
    
    /**
     * @brief X coordinate for hit animation when moving down
     */
    int hitDownX;
    
    /**
     * @brief Source rectangle for death animation sprite
     */
    SDL_Rect deathRect;
    
    /**
     * @brief Rotation angle of the entity
     */
    double rotation;
    
    /**
     * @brief Score increase value when entity is destroyed
     */
    int increase;
    
    /**
     * @brief Sprite texture ID for upgrade drops
     */
    std::string upgradeSprite;
    
    /**
     * @brief Source rectangle for upgrade sprite
     */
    SDL_Rect upgradeSrcRect;
    
    /**
     * @brief Width of upgrade drop
     */
    int upgradeWidth;
    
    /**
     * @brief Height of upgrade drop
     */
    int upgradeHeight;
    
    /**
     * @brief Rotation of upgrade drop
     */
    int upgradeRotation;
    
    /**
     * @brief Collision radius of upgrade drop
     */
    int upgradeRadius;
    
    /**
     * @brief Lua function executed when upgrade is collected
     */
    sol::function upgradeFunction;
    
    /**
     * @brief Sound effect for upgrade collection
     */
    std::string upgradeSound;
    
    /**
     * @brief Flag indicating if entity has attack capability
     */
    bool hasAttack;
    
    /**
     * @brief Flag indicating if entity has animation
     */
    bool hasAnimation;
    
    /**
     * @brief Flag indicating if entity drops items on death
     */
    bool hasDrop;
    
    /**
     * @brief Flag indicating if entity has sound effects
     */
    bool hasSound;
    
    /**
     * @brief X coordinate for spawn position
     */
    int spawnX;
    
    /**
     * @brief Y coordinate for spawn position
     */
    int spawnY;

public:
    /**
     * @brief Group identifier for entity grouping
     */
    int groupNumber;
    
    /**
     * @brief Number of entities remaining in the group
     */
    int groupLeft;
    
    /**
     * @brief Maximum number of entities to spawn
     */
    int spawnMax;
    
    /**
     * @brief Wait time between spawns in ticks
     */
    int spawnWait;
    
    /**
     * @brief Number of entities already spawned
     */
    int spawnedAmount;
    
    /**
     * @brief Lua function for entity update logic
     */
    sol::function update;
    
    /**
     * @brief Timestamp of last spawn event
     */
    int lastSpawnTick;
    
    /**
     * @brief Flag indicating if this is a boss entity
     */
    bool isBoss;
    
    /**
     * @brief X coordinate for boss spawn position
     */
    int bossX;
    
    /**
     * @brief Y coordinate for boss spawn position
     */
    int bossY;
    
    /**
     * @brief Constructs a new PreEntity with group configuration
     * 
     * @param groupNumber Identifier for the entity group
     * @param groupLeft Number of entities remaining in group (default: 1)
     * @param spawnWait Wait time between spawns (default: 1)
     */
    PreEntity(int groupNumber, int groupLeft = 1, int spawnWait = 1);
    
    /**
     * @brief Configures animation properties for the entity
     * 
     * @param numFrames Number of animation frames (default: 1)
     * @param frameRate Animation frame rate (default: 1)
     * @param isLoop Whether animation should loop (default: true)
     */
    void SetAnimation(int numFrames = 1, int frameRate = 1, bool isLoop = true);
    
    /**
     * @brief Configures attack properties and behavior
     * 
     * @param damage Attack damage (default: 1)
     * @param radius Attack collision radius (default: 0)
     * @param width Attack area width (default: 0)
     * @param height Attack area height (default: 0)
     * @param textureId Attack texture identifier (default: "none")
     * @param srcX Source rectangle X coordinate (default: 0)
     * @param srcY Source rectangle Y coordinate (default: 0)
     * @param velVec Attack projectile velocity (default: (0,0))
     * @param soundFile Shooting sound file path (default: "")
     * @param hitSoundFilePath Hit sound file path (default: "none")
     * @param maxShots Maximum shots allowed (default: 0)
     * @param left Left-facing attack flag (default: false)
     * @param scale Attack visual scale (default: (1,1))
     * @param shotQuantity Projectiles per shot (default: 1)
     * @param update Lua update function (default: nil)
     * @param numFrames Attack animation frames (default: 1)
     * @param frameSpeedRate Attack animation speed (default: 1)
     * @param isLoop Attack animation loop flag (default: true)
     */
    void SetAttack(int damage = 1, int radius = 0, int width = 0, int height = 0,
                   const std::string& textureId = "none", int srcX = 0, int srcY = 0,
                   glm::vec2 velVec = glm::vec2(0.0, 0.0), std::string soundFile = "",
                   std::string hitSoundFilePath = "none", int maxShots = 0, bool left = false,
                   glm::vec2 scale = glm::vec2(1.0, 1.0), int shotQuantity = 1,
                   sol::function update = sol::lua_nil, int numFrames = 1,
                   int frameSpeedRate = 1, bool isLoop = true);
    
    /**
     * @brief Configures collision detection properties
     * 
     * @param radius Circular collision radius (default: 0)
     * @param width Rectangular collision width (default: 0)
     * @param height Rectangular collision height (default: 0)
     */
    void SetCollider(int radius = 0, int width = 0, int height = 0);
    
    /**
     * @brief Configures enemy AI behavior
     * 
     * @param update Lua function for enemy update logic (default: nil)
     */
    void SetEnemy(sol::function update = sol::lua_nil);
    
    /**
     * @brief Configures health and damage properties
     * 
     * @param health Entity health points (default: 1)
     * @param damage Damage dealt to other entities (default: 1)
     */
    void SetHealth(int health = 1, int damage = 1);
    
    /**
     * @brief Configures physics body properties
     * 
     * @param velocity Movement velocity vector (default: (0,0))
     */
    void SetBody(glm::vec2 velocity = glm::vec2(0.0, 0.0));
    
    /**
     * @brief Configures sound effects
     * 
     * @param soundPath File path to sound effect (default: "none")
     */
    void SetSound(const std::string& soundPath = "none");
    
    /**
     * @brief Configures sprite rendering and animation states
     * 
     * @param textureId Main sprite texture ID (default: "none")
     * @param srcRectX Main sprite source X (default: 0)
     * @param srcRectY Main sprite source Y (default: 0)
     * @param hitRectX Hit animation source X (default: 0)
     * @param hitRectY Hit animation source Y (default: 0)
     * @param upX Upward movement sprite X (default: 0)
     * @param downX Downward movement sprite X (default: 0)
     * @param hitUpX Hit animation upward X (default: 0)
     * @param hitDownX Hit animation downward X (default: 0)
     * @param deathRectX Death animation source X (default: 0)
     * @param deathRectY Death animation source Y (default: 0)
     */
    void SetSprite(const std::string& textureId = "none", int srcRectX = 0,
                   int srcRectY = 0, int hitRectX = 0, int hitRectY = 0,
                   int upX = 0, int downX = 0, int hitUpX = 0, int hitDownX = 0,
                   int deathRectX = 0, int deathRectY = 0);
    
    /**
     * @brief Configures transformation properties
     * 
     * @param scale Scale factor for the entity (default: (1,1))
     * @param rotation Rotation angle in degrees (default: 0.0)
     */
    void SetTransform(glm::vec2 scale = glm::vec2(1.0, 1.0), double rotation = 0.0);
    
    /**
     * @brief Configures item drop behavior on entity death
     * 
     * @param increase Score increase value (default: 1)
     * @param Unnamed Lua function for drop behavior (default: nil)
     * @param width Drop item width (default: 0)
     * @param height Drop item height (default: 0)
     * @param rotation Drop item rotation (default: 0)
     * @param textureId Drop item texture ID (default: "none")
     * @param x Drop spawn X coordinate (default: 0)
     * @param y Drop spawn Y coordinate (default: 0)
     * @param soundName Drop collection sound (default: "none")
     * @param radius Drop collision radius (default: 0)
     */
    void SetDrop(int increase = 1, sol::function = sol::lua_nil, int width = 0,
                 int height = 0, double rotation = 0, const std::string& textureId = "none",
                 int x = 0, int y = 0, const std::string& soundName = "none", int radius = 0);
    
    /**
     * @brief Creates and spawns the actual entity in the ECS registry
     * 
     * Takes all configured properties and creates a complete entity
     * with all necessary components in the provided registry.
     * 
     * @param registry ECS registry to create the entity in
     */
    void CreateEntity(std::unique_ptr<Registry>& registry);
    
    /**
     * @brief Sets the spawn position for the entity
     * 
     * @param x X coordinate for spawn position
     * @param y Y coordinate for spawn position
     */
    void SetSpawn(int x, int y);
    
    /**
     * @brief Configures entity as a boss with specific spawn position
     * 
     * @param x X coordinate for boss spawn position
     * @param y Y coordinate for boss spawn position
     */
    void SetBoss(int x, int y);
};
#endif // PREENTITY_HPP