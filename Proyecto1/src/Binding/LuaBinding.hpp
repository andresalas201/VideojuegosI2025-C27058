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

bool IsActionActivated(const std::string& action) {
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}

void SetVelocity(Entity entity, float x, float y) {
    auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
    rigidBody.velocity.x = x;
    rigidBody.velocity.y = y;
}

void SetSprite (Entity entity) {
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

glm::vec2 CalculatePosition(Entity e, bool left) {
    double direction;
    if (left) direction = -1.0;
    else direction = 1.0;
    glm::vec2 entityPosition = e.GetComponent<TransformComponent>().position;
    int entityWidth = e.GetComponent<SpriteComponent>().width;
    int entityHeight = e.GetComponent<SpriteComponent>().height;
    int entityScaleX = e.GetComponent<TransformComponent>().scale.x;
    int entityScaleY = e.GetComponent<TransformComponent>().scale.y;
    double x = (entityPosition.x + ((entityWidth / 2 ) * entityScaleX)) + 
        ((entityWidth) * direction);
    double y = entityPosition.y + (entityHeight/ 2) * entityScaleY - entityHeight / 2;
    glm::vec2 result = glm::vec2(x, y);
    return result;

}
glm::vec2 CalculatePosition(Entity e, bool left, bool up) {
    double direction;
    if (left) direction = -1.0;
    else direction = 1.0;
    glm::vec2 entityPosition = e.GetComponent<TransformComponent>().position;
    int entityWidth = e.GetComponent<SpriteComponent>().width;
    int entityHeight = e.GetComponent<SpriteComponent>().height;
    int entityScaleX = e.GetComponent<TransformComponent>().scale.x;
    int entityScaleY = e.GetComponent<TransformComponent>().scale.y;
    double x = (entityPosition.x + ((entityWidth / 2 ) * entityScaleX)) + 
        ((entityWidth) * direction);
    double y;
    if (up) y = entityPosition.y;
    else y = (entityPosition.y + (entityHeight * entityScaleY));
    glm::vec2 result = glm::vec2(x, y);
    return result;

}

bool CanShoot(AttackComponent* attack) {
    int ticksSinceShot = (SDL_GetTicks() - attack->lastShotTick);
    return ticksSinceShot >= MILLISECS_PER_FRAME * FPS;
}

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

void UpgradeDamage(Entity upgraded, int increase) {
    if(!upgraded.HasComponent<AttackComponent>()) return;
    upgraded.GetComponent<AttackComponent>().damage += increase;
    std::cout << "Entity " << upgraded.GetId() << " aumenta su daño por " << increase <<
        " a " << upgraded.GetComponent<AttackComponent>().damage << std::endl;
}

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

void UpgradeSpeed(Entity upgraded, int increase) {
    if(!upgraded.HasComponent<RigidBodyComponent>()) return;
    auto& rigidBody = upgraded.GetComponent<RigidBodyComponent>();
    rigidBody.velocity += static_cast<double>(increase);
}

// Scenes

void GoToScene(const std::string& sceneName) {
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

// Background Move

void BackgroundMove(Entity a) {
    int position = a.GetComponent<TransformComponent>().position.x;
    int width = a.GetComponent<SpriteComponent>().width;
    if (((position + width) <= Game::GetInstance().windowWidth)) {
        SetVelocity(a, 1.0, 0.0);
    }
}

void SpawnBoss(Entity a) {
    Game::GetInstance().eventManager->EmitEvent<BossSpawnEvent>(a);
    std::cout << "Se spawnea el jefe";
}

void SetRotation(Entity a, float x, float y) {
    auto& transform = a.GetComponent<TransformComponent>();
    if (x > 0) {
        if (y > 0) transform.rotation = 315;
        else if (y < 0) transform.rotation = 45;
        else transform.rotation = 0;
    } else if (x < 0) {
        if (y > 0) transform.rotation = 135;
        else if (y < 0) transform.rotation = 225;
        else transform.rotation = 180;
    } else {
        if (y > 0) transform.rotation = 90;
        else if (y < 0) transform.rotation = 270;
        else transform.rotation = 0;
    }
}

double CalculateDistance(float x1, float y1, float x2, float y2) {
    return sqrt(static_cast<double>(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))));
} 

void SetDirectionToPlayer(Entity a) {
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

#endif // LUABINDING_HPP