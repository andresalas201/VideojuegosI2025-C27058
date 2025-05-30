/**
 * @file LuaBinding.hpp
 * @brief Lua binding functions for game entity manipulation and control
 */

#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>

#include "../ECS/ECS.hpp"
#include "../Events/BossSpawnEvent.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../Game/Game.hpp"
#include "../Systems/AudioSystem.hpp"
#include "../Systems/CollisionSystem.hpp"
#include "../Systems/HealthBarSystem.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/SoundComponent.hpp"
#include "../Components/AttackComponent.hpp"
#include "../Components/FatherComponent.hpp"
#include "../Components/ShotComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/PlayerComponent.hpp"

/**
 * @brief Checks if a specific input action is currently activated
 * 
 * Queries the game's controller manager to determine if the specified
 * action is currently being triggered by player input.
 * 
 * @param action String identifier of the action to check
 * @return true if the action is activated, false otherwise
 */
bool IsActionActivated(const std::string& action) {
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}

/**
 * @brief Sets the velocity of an entity's rigid body component
 * 
 * Updates the velocity of the entity and refreshes the health bar
 * if the entity is a player with a health component.
 * 
 * @param entity The entity whose velocity will be modified
 * @param x Horizontal velocity component
 * @param y Vertical velocity component
 */
void SetVelocity(Entity entity, float x, float y) {
    if (!entity.HasComponent<RigidBodyComponent>()) return;
    auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
    rigidBody.velocity.x = x;
    rigidBody.velocity.y = y;
    if (entity.HasComponent<PlayerComponent>() && entity.HasComponent<HealthComponent>()) {
        entity.registry->GetSystem<HealthBarSystem>().SetHealth(
            entity.GetComponent<HealthComponent>().health, 
            entity.GetComponent<PlayerComponent>().playerNumber - 1);
    }
}

/**
 * @brief Updates sprite animation based on entity movement direction
 * 
 * Changes the sprite's source rectangle coordinates based on the
 * entity's vertical velocity to show appropriate directional animation.
 * 
 * @param entity The entity whose sprite will be updated
 */
void SetSprite (Entity entity) {
    if (!entity.HasComponent<SpriteComponent>() || !entity.HasComponent<RigidBodyComponent>()) return;
    auto& sprite = entity.GetComponent<SpriteComponent>();
    auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
    if (rigidBody.velocity.y < 0.0) {
        sprite.srcRect.x = sprite.upX;
        sprite.hitSrcRect.x = sprite.hitUpX;
    }
    else if (rigidBody.velocity.y > 0.0) {
        sprite.srcRect.x = sprite.downX;
        sprite.hitSrcRect.x = sprite.hitDownX;
    }
    else {
        sprite.srcRect.x = sprite.srcRectBase;
        sprite.hitSrcRect.x = sprite.hitSrcRectBase;
    }
}

/**
 * @brief Calculates a spawn position relative to an entity
 * 
 * Determines a position to the left or right of the entity based on
 * its transform and sprite dimensions, typically used for projectile spawning.
 * 
 * @param e The reference entity
 * @param left If true, calculates position to the left; otherwise to the right
 * @return glm::vec2 The calculated world position
 */
glm::vec2 CalculatePosition(Entity e, bool left) {
    if (!e.HasComponent<TransformComponent>() || !e.HasComponent<SpriteComponent>()) return glm::vec2(-10, -10);
    
    double direction = 0;
    if(left) direction = -1.0;
    else direction = 1.0;
    
    glm::vec2 entityPosition = e.GetComponent<TransformComponent>().position;
    int entityWidth = e.GetComponent<SpriteComponent>().width;
    int entityHeight = e.GetComponent<SpriteComponent>().height;
    
    double entityScaleX = e.GetComponent<TransformComponent>().scale.x;
    double entityScaleY = e.GetComponent<TransformComponent>().scale.y;
    
    double scaledWidth = entityWidth * entityScaleX;
    double scaledHeight = entityHeight * entityScaleY;
    
    double x = entityPosition.x + (scaledWidth / 2.0) + (scaledWidth * direction);
    
    double y = entityPosition.y + (scaledHeight / 2.0);
    
    glm::vec2 result = glm::vec2(x, y);
    
    return result;
}

/**
 * @brief Calculates a spawn position relative to an entity with vertical offset
 * 
 * Extended version of CalculatePosition that also considers vertical positioning
 * (top or bottom of the entity) in addition to horizontal positioning.
 * 
 * @param e The reference entity
 * @param left If true, calculates position to the left; otherwise to the right
 * @param up If true, calculates position at the top; otherwise at the bottom
 * @return glm::vec2 The calculated world position
 */
glm::vec2 CalculatePosition(Entity e, bool left, bool up) {
    if (!e.HasComponent<TransformComponent>() || !e.HasComponent<SpriteComponent>()) return glm::vec2(-10, -10);
 
    double direction = 0;
    if(left) direction = -1.0;
    else direction = 1.0;
    
    glm::vec2 entityPosition = e.GetComponent<TransformComponent>().position;
    int entityWidth = e.GetComponent<SpriteComponent>().width;
    int entityHeight = e.GetComponent<SpriteComponent>().height;
    
    double entityScaleX = e.GetComponent<TransformComponent>().scale.x;
    double entityScaleY = e.GetComponent<TransformComponent>().scale.y;
    
    double scaledWidth = entityWidth * entityScaleX;
    double scaledHeight = entityHeight * entityScaleY;
    
    double x = entityPosition.x + (scaledWidth / 2.0) + (scaledWidth * direction);
    
    double y;
    if (up) {
        y = entityPosition.y;
    } else {
        y = entityPosition.y + scaledHeight; 
    }
    
    return glm::vec2(x, y);
}

/**
 * @brief Checks if an entity can shoot based on attack cooldown
 * 
 * Determines if enough time has passed since the last shot based on
 * the game's frame rate and timing system.
 * 
 * @param attack Pointer to the attack component to check
 * @return true if the entity can shoot, false if still on cooldown
 */
bool CanShoot(AttackComponent* attack) {
    int ticksSinceShot = (SDL_GetTicks() - attack->lastShotTick);
    return ticksSinceShot >= MILLISECS_PER_FRAME * FPS;
}

/**
 * @brief Creates an additional projectile with vertical movement
 * 
 * Spawns an extra shot entity with upward or downward movement,
 * typically used for multi-shot attacks or spread patterns.
 * 
 * @param shooter The entity that is shooting
 * @param attack Pointer to the attack component containing shot parameters
 * @param up If true, projectile moves upward; otherwise downward
 */
void ShootExtra(Entity shooter,AttackComponent* attack, bool up) {
    Entity shot = Game::GetInstance().registry->CreateEntity();
    shot.AddComponent<CircleColliderComponent>(attack->radius, attack->width,
        attack->height);
    glm::vec2 velocity = attack->velocity;
    if (up) velocity.y = -25;
    else velocity.y = 25;
    shot.AddComponent<RigidBodyComponent>(velocity);
    shot.AddComponent<TransformComponent>(CalculatePosition(shooter, attack->left, up), 
        attack->scale, 0);
    shot.AddComponent<HealthComponent>(1, attack->damage);
    shot.AddComponent<CircleColliderComponent>(attack->radius, attack->width,
        attack->height);
    shot.AddComponent<SpriteComponent>(attack->textureId, attack->width,
        attack->srcRect.x, attack->srcRect.y);
    shot.AddComponent<SoundComponent>(attack->hitSoundFilePath);
    shot.AddComponent<FatherComponent>(attack);
    shot.AddComponent<ShotComponent>(true, shooter.HasComponent<PlayerComponent>());
    shot.AddComponent<AnimationComponent>(attack->numFrames, attack->frameSpeedRate, attack->isLoop);
    attack->currentShots++;
    Game::GetInstance().registry->AddEntityToSystems(shot);
}

/**
 * @brief Creates a projectile entity from a shooter
 * 
 * Spawns a shot entity with all necessary components based on the
 * shooter's attack component. Handles cooldown, shot limits, and
 * multi-shot patterns.
 * 
 * @param shooter The entity that will create the projectile
 */
void Shoot(Entity shooter) {
    if(!shooter.HasComponent<AttackComponent>()) return;
    AttackComponent* attack = &shooter.GetComponent<AttackComponent>();
    if (attack && attack->currentShots < attack->maxShots && CanShoot(attack)) {
        Entity shot = Game::GetInstance().registry->CreateEntity();
        shot.AddComponent<CircleColliderComponent>(attack->radius, attack->width,
            attack->height);
        shot.AddComponent<RigidBodyComponent>(attack->velocity);
        shot.AddComponent<TransformComponent>(CalculatePosition(shooter, attack->left), 
            attack->scale, attack->shotQuantity);
        shot.AddComponent<HealthComponent>(1, attack->damage);
        shot.AddComponent<CircleColliderComponent>(attack->radius, attack->width,
            attack->height);
        shot.AddComponent<SpriteComponent>(attack->textureId, attack->width,
            attack->srcRect.x, attack->srcRect.y);
        shot.AddComponent<SoundComponent>(attack->hitSoundFilePath);
        shot.AddComponent<FatherComponent>(attack);
        shot.AddComponent<ShotComponent>(true, shooter.HasComponent<PlayerComponent>());
        shot.AddComponent<ScriptComponent>(attack->update);
        shot.AddComponent<AnimationComponent>(attack->numFrames, attack->frameSpeedRate, attack->isLoop);
        attack->currentShots++;
        attack->lastShotTick = SDL_GetTicks();
        Game::GetInstance().registry->GetSystem<AudioSystem>().playSound(
            Game::GetInstance().assetManager->GetSound(attack->shootSoundFilePath)
        );
        Game::GetInstance().registry->AddEntityToSystems(shot);
        if (attack->shotQuantity > 1) ShootExtra(shooter, attack, true);
        if (attack->shotQuantity > 2) ShootExtra(shooter, attack, false);
    }
}

/**
 * @brief Increases an entity's attack damage
 * 
 * Adds the specified damage increase to the entity's attack component
 * and logs the upgrade to console.
 * 
 * @param upgraded The entity to upgrade
 * @param increase Amount of damage to add
 */
void UpgradeDamage(Entity upgraded, int increase) {
    if(!upgraded.HasComponent<AttackComponent>()) return;
    upgraded.GetComponent<AttackComponent>().damage += increase;
    std::cout << "Entity " << upgraded.GetId() << " aumenta su daño por " << increase <<
        " a " << upgraded.GetComponent<AttackComponent>().damage << std::endl;
}

/**
 * @brief Increases an entity's shot quantity or damage if at maximum
 * 
 * Upgrades the entity's attack by increasing the number of simultaneous
 * shots. If already at maximum shot quantity (3), upgrades damage instead.
 * 
 * @param upgraded The entity to upgrade
 */
void UpgradeAmount(Entity upgraded) {
    if(!upgraded.HasComponent<AttackComponent>()) return;
    auto& attack = upgraded.GetComponent<AttackComponent>();
    if (attack.shotQuantity >= 3) {
        UpgradeDamage(upgraded, 2);
        return;
    }
    attack.maxShots /= attack.shotQuantity;
    attack.shotQuantity += 1;
    attack.maxShots *= attack.shotQuantity;
    std::cout << "Entity " << upgraded.GetId() << " aumenta su shot quantity"
        " a " << upgraded.GetComponent<AttackComponent>().shotQuantity << std::endl;
}

/**
 * @brief Increases an entity's movement speed
 * 
 * Adds the specified speed increase to the entity's rigid body velocity.
 * 
 * @param upgraded The entity to upgrade
 * @param increase Amount of speed to add
 */
void UpgradeSpeed(Entity upgraded, int increase) {
    if(!upgraded.HasComponent<RigidBodyComponent>()) return;
    auto& rigidBody = upgraded.GetComponent<RigidBodyComponent>();
    rigidBody.velocity += static_cast<double>(increase);
}

/**
 * @brief Transitions to a different game scene
 * 
 * Sets the next scene to load and stops the current scene,
 * triggering a scene transition.
 * 
 * @param sceneName Name of the scene to transition to
 */
void GoToScene(const std::string& sceneName) {
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

/**
 * @brief Implements bouncing movement for background elements
 * 
 * Reverses the entity's velocity when it reaches screen boundaries,
 * creating a bouncing effect typically used for background decorations.
 * 
 * @param a The entity to apply bouncing movement to
 */
void BackgroundMove(Entity a) {
    if (!a.HasComponent<TransformComponent>() || !a.HasComponent<SpriteComponent>() ||
        !a.HasComponent<RigidBodyComponent>()) return;
    int positionX = a.GetComponent<TransformComponent>().position.x;
    int positionY = a.GetComponent<TransformComponent>().position.x;
    int width = a.GetComponent<SpriteComponent>().width;
    int height = a.GetComponent<SpriteComponent>().height;
    float currentX = a.GetComponent<RigidBodyComponent>().velocity.x;
    float currentY = a.GetComponent<RigidBodyComponent>().velocity.y;
    if (((positionX + width) <= Game::GetInstance().windowWidth) || positionX < 0) {
        currentX *= -1.0;
    }
    if (((positionY + height) <= Game::GetInstance().windowHeight) || positionY < 0) {
        currentY *= -1.0;
    }
    SetVelocity(a, currentX, currentY);
}

/**
 * @brief Triggers a boss spawn event
 * 
 * Emits a boss spawn event through the event system and logs
 * the spawn to console.
 * 
 * @param a The entity that triggers the boss spawn
 */
void SpawnBoss(Entity a) {
    Game::GetInstance().eventManager->EmitEvent<BossSpawnEvent>(a);
    std::cout << "Se spawnea el jefe";
}

/**
 * @brief Sets entity rotation based on direction vector
 * 
 * Calculates and sets the entity's rotation angle based on the
 * provided direction components, normalizing to 0-360 degree range.
 * 
 * @param a The entity to rotate
 * @param x Horizontal direction component
 * @param y Vertical direction component
 */
void SetRotation(Entity a, float x, float y) {
    if (!a.HasComponent<TransformComponent>()) return;
    auto& transform = a.GetComponent<TransformComponent>();
    if (x != 0 || y != 0) {
        transform.rotation = atan2(y, x) * 180.0f / M_PI;
        
        // Normalize to 0-360 range
        if (transform.rotation < 0) {
            transform.rotation += 360;
        }
    }
}

/**
 * @brief Calculates Euclidean distance between two points
 * 
 * Computes the straight-line distance between two 2D coordinates
 * using the Pythagorean theorem.
 * 
 * @param x1 X coordinate of first point
 * @param y1 Y coordinate of first point
 * @param x2 X coordinate of second point
 * @param y2 Y coordinate of second point
 * @return double The distance between the two points
 */
double CalculateDistance(float x1, float y1, float x2, float y2) {
    return sqrt(static_cast<double>(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))));
} 

/**
 * @brief Sets entity movement direction toward the nearest player
 * 
 * Finds the closest player entity and sets the entity's velocity to move
 * toward that player with appropriate speed limits and rotation.
 * 
 * @param a The entity that will move toward the player
 */
void SetDirectionToPlayer(Entity a) {
    if (!a.HasComponent<TransformComponent>()) return;
    float enemyX = a.GetComponent<TransformComponent>().position.x;
    float enemyY = a.GetComponent<TransformComponent>().position.y;
    float playerX = 0, playerY = 0;
    float xFinal = 0;
    float yFinal = 0;
    double currentClosest = 10000.0;
    double currentDistance = 10000.0;
    for (auto entity : a.registry->GetSystem<CollisionSystem>().GetSystemEntities()) {
        if (entity.HasComponent<PlayerComponent>() && 
            entity.HasComponent<TransformComponent>()) {
            
            playerX = entity.GetComponent<TransformComponent>().position.x;
            playerY = entity.GetComponent<TransformComponent>().position.y;
            currentDistance = CalculateDistance(enemyX, enemyY, playerX, playerY);
            if (currentClosest > currentDistance) {
                currentClosest = currentDistance;
                xFinal = playerX;
                yFinal = playerY;
            }
        }
    }
    float speedX;
    float speedY;
    
    // Calculates if it should go left or right
    if ((enemyX - xFinal) > 0.0) {
        // Move left by the remaining distance
        if ((enemyX - xFinal) < 100.0) speedX = -(enemyX - xFinal);
        else speedX = -100.0;
    }
    else if ((enemyX - xFinal) < 0.0) {
        // Move right by the remaining distance
        if ((enemyX - xFinal) > -100.0) speedX = -(enemyX - xFinal);
        else speedX = 100.0;
    } else speedX = 0;

    // Calculates if it should go up or down
    if ((enemyY - yFinal) > 0) {
        if ((enemyY - yFinal)) speedY = -(enemyY - yFinal);
        else speedY = -100.0;
    }
    else if ((enemyY - yFinal) < 0) {
        if ((enemyY - yFinal)) speedY = -(enemyY - yFinal);
        else speedY = 100.0;
    }
    else speedY = 0;
    SetVelocity(a, speedX, speedY);
    SetRotation(a, speedX, speedY);
}

/**
 * @brief Sets boss entity movement direction toward the nearest player
 * 
 * Similar to SetDirectionToPlayer but with slower movement speed (25 units)
 * specifically designed for boss entities without rotation updates.
 * 
 * @param a The boss entity that will move toward the player
 */
void SetDirectionToPlayerBoss(Entity a) {
    if (!a.HasComponent<TransformComponent>()) return;
    float enemyX = a.GetComponent<TransformComponent>().position.x;
    float enemyY = a.GetComponent<TransformComponent>().position.y;
    float playerX = 0, playerY = 0;
    float xFinal = 0;
    float yFinal = 0;
    double currentClosest = 10000.0;
    double currentDistance = 10000.0;
    for (auto entity : a.registry->GetSystem<CollisionSystem>().GetSystemEntities()) {
        if (entity.HasComponent<PlayerComponent>() && 
            entity.HasComponent<TransformComponent>()) {
            
            playerX = entity.GetComponent<TransformComponent>().position.x;
            playerY = entity.GetComponent<TransformComponent>().position.y;
            currentDistance = CalculateDistance(enemyX, enemyY, playerX, playerY);
            if (currentClosest > currentDistance) {
                currentClosest = currentDistance;
                xFinal = playerX;
                yFinal = playerY;
            }
        }
    }
    float speedX;
    float speedY;
    
    // Calculates if it should go left or right
    if ((enemyX - xFinal) > 0.0) {
        // Move left by the remaining distance
        if ((enemyX - xFinal) < 25.0) speedX = -(enemyX - xFinal);
        else speedX = -25.0;
    }
    else if ((enemyX - xFinal) < 0.0) {
        // Move right by the remaining distance
        if ((enemyX - xFinal) > -25.0) speedX = -(enemyX - xFinal);
        else speedX = 25.0;
    } else speedX = 0;

    // Calculates if it should go up or down
    if ((enemyY - yFinal) > 0) {
        if ((enemyY - yFinal)) speedY = -(enemyY - yFinal);
        else speedY = -25.0;
    }
    else if ((enemyY - yFinal) < 0) {
        if ((enemyY - yFinal)) speedY = -(enemyY - yFinal);
        else speedY = 25.0;
    }
    else speedY = 0;
    SetVelocity(a, speedX, speedY);
}

/**
 * @brief Initiates player following behavior when entity is stationary
 * 
 * Checks if the entity has zero velocity and, if so, sets its direction
 * toward the nearest player. Used for simple AI behavior.
 * 
 * @param a The entity that should follow the player
 */
void FollowPlayerSimple(Entity a) {
    if (!a.HasComponent<RigidBodyComponent>() ) return;
    float velX = a.GetComponent<RigidBodyComponent>().velocity.x;
    float velY = a.GetComponent<RigidBodyComponent>().velocity.y;
    if (velX == 0.0 && velY == 0.0) {
        SetDirectionToPlayer(a);
    }
}

#endif // LUABINDING_HPP