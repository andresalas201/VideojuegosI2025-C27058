#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <iostream>
#include <glm/glm.hpp>

#include "../ECS/ECS.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../Game/Game.hpp"
#include "../Systems/AudioSystem.hpp"
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
    double x = (entityPosition.x + ((entityWidth / 2 ) * entityScaleX)) + 
        ((entityWidth) * direction);
    double y;
    if (up) y = entityPosition.y;
    else y = entityPosition.y + entityHeight;
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

#endif // LUABINDING_HPP